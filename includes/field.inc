<?php


/**
 * Implementation of theme_field().
 *
 * Remove all unnecessary markup. (cheapo fences)
 */
function frontend_field($variables) {
  $output = '';
  foreach ($variables['items'] as $delta => $item) {
    $output .= drupal_render($item);
  }
  return $output;
}

