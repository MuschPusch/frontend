<?php
/**
 * @file
 * forms.inc
 */

/**
 * Implement theme_form().
 */
function frontend_form($variables) {
  $element = $variables ['element'];
  if (isset($element ['#action'])) {
    $element ['#attributes']['action'] = drupal_strip_dangerous_protocols($element ['#action']);
  }
  element_set_attributes($element, array('method', 'id'));
  if (empty($element ['#attributes']['accept-charset'])) {
    $element ['#attributes']['accept-charset'] = "UTF-8";
  }
  $element ['#attributes']['class'][] = 'Form';

  return '<form' . drupal_attributes($element ['#attributes']) . '>' . $element ['#children'] . '</form>';
}

/**
 * Implements theme_form_element().
 */
function frontend_form_element($variables) {
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
 * Implements theme_textfield().
 */
function frontend_textfield($variables) {
  $element = $variables ['element'];
  $element ['#attributes']['type'] = 'text';
  element_set_attributes($element, array('id', 'name', 'value', 'size', 'maxlength'));
  _form_set_class($element, array('Form-input', 'Form-input--text'));

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
 * Implements theme_textarea().
 */
function frontend_textarea($variables) {
  $element = $variables ['element'];
  element_set_attributes($element, array('id', 'name', 'cols', 'rows'));
  _form_set_class($element, array('Form-input', 'Form-input--textarea'));

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
