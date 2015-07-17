<?php

/**
 * Implementation of theme_field().
 */
function frontend_field($variables) {
  $element = $variables['element'];
  $entity_id = entity_extract_ids($element['#entity_type'], $element['#object']);
  $output = '';
  foreach ($variables['items'] as $delta => $item) {
    $output .= frontend_fedit($item, $element['#entity_type'], $element['#bundle'], $entity_id[0], $element['#field_name'], TRUE);
  }
  return $output;
}
