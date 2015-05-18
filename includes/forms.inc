<?php
/**
 * @file
 * forms.inc
 */


function frontend_ignore_customizations() {
  return ((arg(0) == 'panels') && (arg(1) == 'ajax'));
}

/**
 * Implement theme_form().
 */
function frontend_form($variables) {
  if (frontend_ignore_customizations()) {
    return theme_form($variables);
  }

  $element = $variables['element'];
  if (isset($element ['#action'])) {
    $element ['#attributes']['action'] = drupal_strip_dangerous_protocols($element ['#action']);
  }
  element_set_attributes($element, array('method', 'id'));
  if (empty($element ['#attributes']['accept-charset'])) {
    $element ['#attributes']['accept-charset'] = "UTF-8";
  }

  if (empty($element['#modifier'])) {
    $element['#modifier'] = NULL;
  }
  $element ['#attributes']['class'][] = 'Form ' . $element['#modifier'];

  return '<form' . drupal_attributes($element ['#attributes']) . '>' . $element ['#children'] . '</form>';
}

/**
 * Implements theme_form_element().
 */
function frontend_form_element($variables) {
  if (frontend_ignore_customizations()) {
    return theme_form_element($variables);
  }

  $element = &$variables['element'];

  // This function is invoked as theme wrapper, but the rendered form element
  // may not necessarily have been processed by form_builder().
  $element += array(
    '#title_display' => 'before',
  );

  // Add element #id for #type 'item'.
  if (isset($element['#markup']) && !empty($element['#id'])) {
    $attributes['id'] = $element['#id'];
  }
  // Add element's #type and #name as class to aid with JS/CSS selectors.
  $attributes['class'] = array('Form-item');
  if (!empty($element['#type'])) {
    $attributes['class'][] = 'Form-item--' . strtr($element['#type'], '_', '-');
  }
  if (!empty($element['#name'])) {
    $attributes['class'][] = 'Form-item--' . strtr($element['#name'], array(' ' => '-', '_' => '-', '[' => '-', ']' => ''));
  }
  // Add a class for disabled elements to facilitate cross-browser styling.
  if (!empty($element['#attributes']['disabled'])) {
    $attributes['class'][] = 'is-disabled';
  }

  $output = '<div' . drupal_attributes($attributes) . '>' . "\n";

  // If #title is not set, we don't display any label or required marker.
  if (!isset($element['#title'])) {
    $element['#title_display'] = 'none';
  }
  $prefix = isset($element['#field_prefix']) ? '<span class="Form-item-prefix">' . $element['#field_prefix'] . '</span> ' : '';
  $suffix = isset($element['#field_suffix']) ? ' <span class="Form-item-suffix">' . $element['#field_suffix'] . '</span>' : '';

  switch ($element['#title_display']) {
    case 'before':
    case 'invisible':
      $output .= ' ' . theme('form_element_label', $variables);
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;

    case 'after':
      $output .= ' ' . $prefix . $element['#children'] . $suffix;
      $output .= ' ' . theme('form_element_label', $variables) . "\n";
      break;

    case 'none':
    case 'attribute':
      // Output no label and no required marker, only the children.
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;
  }

  if (!empty($element['#description'])) {
    $output .= '<div class="Form-item-description">' . $element['#description'] . "</div>\n";
  }

  $output .= "</div>\n";

  return $output;
}

/**
 * Implements theme_form_element_label().
 */
function frontend_form_element_label($variables) {
  $element = $variables ['element'];
  // This is also used in the installer, pre-database setup.
  $t = get_t();

  // If title and required marker are both empty, output no label.
  if ((!isset($element ['#title']) || $element ['#title'] === '') && empty($element ['#required'])) {
    return '';
  }

  // If the element is required, a required marker is appended to the label.
  $required = !empty($element ['#required']) ? theme('form_required_marker', array('element' => $element)) : '';

  $title = filter_xss_admin($element ['#title']);

  $attributes = array();

  $attributes['class'] = array('Form-label');

  // Style the label as class option to display inline with the element.
  if ($element ['#title_display'] == 'after') {
    $attributes ['class'] = 'option';
  }
  // Show label only to screen readers to avoid disruption in visual flows.
  elseif ($element ['#title_display'] == 'invisible') {
    $attributes ['class'] = 'is-invisible';
  }

  if (!empty($element ['#id'])) {
    $attributes ['for'] = $element ['#id'];
  }

  // The leading whitespace helps visually separate fields from inline labels.
  return ' <label' . drupal_attributes($attributes) . '>' . $t('!title !required', array('!title' => $title, '!required' => $required)) . "</label>\n";
}

/**
 * Implements theme_form_required_marker().
 */
function frontend_form_required_marker($variables) {
  // This is also used in the installer, pre-database setup.
  $t = get_t();
  $attributes = array(
    'class' => 'Form-required',
    'title' => $t('This field is required.'),
  );
  return '<span' . drupal_attributes($attributes) . '>*</span>';
}

/**
 * Implements theme_textfield().
 */
function frontend_textfield($variables) {
  if (frontend_ignore_customizations()) {
    return theme_textfield($variables);
  }
  $element = $variables ['element'];
  $element ['#attributes']['type'] = 'text';
  element_set_attributes($element, array('id', 'name', 'value', 'size', 'maxlength'));
  frontend_form_set_class($element, array('Form-input', 'Form-input--text'));

  $extra = '';
  if ($element ['#autocomplete_path'] && drupal_valid_path($element ['#autocomplete_path'])) {
    drupal_add_library('system', 'drupal.autocomplete');
    $element ['#attributes']['class'][] = 'Form-input--autocomplete';

    $attributes = array();
    $attributes ['type'] = 'hidden';
    $attributes ['id'] = $element ['#attributes']['id'] . '-autocomplete';
    $attributes ['value'] = url($element ['#autocomplete_path'], array('absolute' => TRUE));
    $attributes ['disabled'] = 'disabled';
    $attributes ['class'][] = 'autocomplete';
    $extra = '<input' . drupal_attributes($attributes) . ' />';
  }

  $output = '<input' . drupal_attributes($element ['#attributes']) . ' />';

  return $output . $extra;
}

/**
 * Implements theme_password().
 */
function frontend_password($variables) {
  if (frontend_ignore_customizations()) {
    return theme_password($variables);
  }
  $element = $variables ['element'];
  $element ['#attributes']['type'] = 'password';
  element_set_attributes($element, array('id', 'name', 'size', 'maxlength'));
  frontend_form_set_class($element, array('Form-input', 'Form-input--text', 'Form-input--password'));

  return '<input' . drupal_attributes($element ['#attributes']) . ' />';
}

/**
 * Implements theme_checkbox().
 */
function frontend_checkbox($variables) {
  if (frontend_ignore_customizations()) {
    return theme_checkbox($variables);
  }
  $element = $variables ['element'];
  $element ['#attributes']['type'] = 'checkbox';
  element_set_attributes($element, array('id', 'name', '#return_value' => 'value'));

  // Unchecked checkbox has #value of integer 0.
  if (!empty($element ['#checked'])) {
    $element ['#attributes']['checked'] = 'checked';
  }
  frontend_form_set_class($element, array('Form-input', 'Form-input--checkbox'));

  return '<input' . drupal_attributes($element ['#attributes']) . ' />';
}

/**
 * Implements theme_radio().
 */
function frontend_radio($variables) {
  if (frontend_ignore_customizations()) {
    return theme_radio($variables);
  }
  $element = $variables ['element'];
  $element ['#attributes']['type'] = 'radio';
  element_set_attributes($element, array('id', 'name', '#return_value' => 'value'));

  if (isset($element ['#return_value']) && $element ['#value'] !== FALSE && $element ['#value'] == $element ['#return_value']) {
    $element ['#attributes']['checked'] = 'checked';
  }
  frontend_form_set_class($element, array('Form-input', 'Form-input--radio'));

  return '<input' . drupal_attributes($element ['#attributes']) . ' />';
}

/**
 * Implements theme_textarea().
 */
function frontend_textarea($variables) {
  if (frontend_ignore_customizations()) {
    return theme_textarea($variables);
  }
  $element = $variables ['element'];
  element_set_attributes($element, array('id', 'name', 'cols', 'rows'));
  frontend_form_set_class($element, array('Form-input', 'Form-input--textarea'));

  // $wrapper_attributes = array(
  //   'class' => array('Form-textarea-wrapper'),
  // );

  // Add resizable behavior.
  // if (!empty($element ['#resizable'])) {
  //   drupal_add_library('system', 'drupal.textarea');
  //   $wrapper_attributes ['class'][] = 'resizable';
  // }

  // $output = '<div' . drupal_attributes($wrapper_attributes) . '>';
  $output .= '<textarea' . drupal_attributes($element ['#attributes']) . '>' . check_plain($element ['#value']) . '</textarea>';
  // $output .= '</div>';
  return $output;
}

/**
 * Implements theme_button().
 */
function frontend_button($variables) {
  if (frontend_ignore_customizations()) {
    return theme_button($variables);
  }
  $element = $variables ['element'];
  $element ['#attributes']['type'] = 'submit';
  element_set_attributes($element, array('id', 'name', 'value'));

  $element ['#attributes']['class'][] = 'Form-input';
  $element ['#attributes']['class'][] = 'Form-input--' . $element ['#button_type'];
  if (!empty($element ['#attributes']['disabled'])) {
    $element ['#attributes']['class'][] = 'is-disabled';
  }

  $wrapper_attributes = array(
    'class' => array('Form-item', 'Form-item--button'),
  );

  $output = '<div' . drupal_attributes($wrapper_attributes) . '>';
  $output .= '<input' . drupal_attributes($element ['#attributes']) . ' />';
  $output .= '</div>';

  return $output;
}

/**
 * Implements theme_container().
 */
function frontend_container($variables) {
  if (frontend_ignore_customizations()) {
    return theme_container($variables);
  }
  $element = $variables ['element'];
  // Ensure #attributes is set.
  $element += array('#attributes' => array());

  // Special handling for form elements.
  if (isset($element ['#array_parents'])) {
    // Assign an html ID.
    if (!isset($element ['#attributes']['id'])) {
      $element ['#attributes']['id'] = $element ['#id'];
    }
    // Add the 'form-wrapper' class.
    $element ['#attributes']['class'] = array('Form-actions');
  }

  return '<div' . drupal_attributes($element ['#attributes']) . '>' . $element ['#children'] . '</div>';
}

/**
 * Implements _form_set_class().
 */
function frontend_form_set_class(&$element, $class = array()) {
  if (!empty($class)) {
    if (!isset($element['#attributes']['class'])) {
      $element['#attributes']['class'] = array();
    }
    $element['#attributes']['class'] = array_merge($element['#attributes']['class'], $class);
  }
  // This function is invoked from form element theme functions, but the
  // rendered form element may not necessarily have been processed by
  // form_builder().
  if (!empty($element['#required'])) {
    $element['#attributes']['class'][] = 'is-required';
  }
  if (isset($element['#parents']) && form_get_error($element) !== NULL && !empty($element['#validated'])) {
    $element['#attributes']['class'][] = 'is-failing';
  }
}
