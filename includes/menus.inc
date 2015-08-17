<?php
/**
 * @file
 * menu helper.
 */


/**
 * Reimplementation of theme_menu_local_tasks().
 */
function xx_frontend_menu_local_tasks(&$variables) {
  $output = '';

  if (!empty($variables['primary'])) {
    $variables ['primary']['#prefix'] = '<h2 class="u-isHiddenVisually">' . t('Primary tabs') . '</h2>';
    $variables ['primary']['#prefix'] .= '<ul class="Tabs Tabs--primary">';
    $variables ['primary']['#suffix'] = '</ul>';
    $output .= drupal_render($variables['primary']);
  }
  if (!empty($variables['secondary'])) {
    $variables ['secondary']['#prefix'] = '<h2 class="u-isHiddenVisually">' . t('Secondary tabs') . '</h2>';
    $variables ['secondary']['#prefix'] .= '<ul class="Tabs Tabs--secondary">';
    $variables ['secondary']['#suffix'] = '</ul>';
    $output .= drupal_render($variables['secondary']);
  }

  return '<div class="TabsWrapper">' . $output . '</div>';
}
