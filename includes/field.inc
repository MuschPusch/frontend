<?php

/**
 * Implementation of theme_field().
 */
function frontend_field($variables) {
  $output = '';
  foreach ($variables['items'] as $delta => $item) {
    $output .= drupal_render($item);
  }
  return $output;
}

function frontend_preprocess_field(&$variables) {
  if (module_exists('fedit')) {
    frontend_fedit_field($variables);
  }
}

/**
 * Wrap the field-content with fedit-wrapper, if necessary.
 */
function frontend_fedit_field(&$variables) {
  if (!user_access('access fedit')) {
    return;
  }

  $element = $variables['element'];
  $entity_id = entity_extract_ids($element['#entity_type'], $element['#object']);

  $data = fedit_entity_get_editable_field(
    $element['#entity_type'],
    $element['#field_name'],
    $element['#bundle'],
    $entity_id[0]);

  if ($data) {
    foreach (array_keys($variables['items']) as $key) {
      $variables['items'][$key]['#markup'] = theme('fedit_wrap', array(
        'content' => $element[$key]['#markup'],
        'data' => $data)
      );
    }
  }
}
