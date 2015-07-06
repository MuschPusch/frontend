<?php
/**
 * @file
 * Helper functions.
 */

/**
 * Implements hook_panels_default_style_render_region().
 */
function frontend_panels_default_style_render_region($vars) {
  $output = '';
  $output .= implode('', $vars['panes']);
  return $output;
}

/**
 * Implementation of hook_css_alter().
 */
function jknr_frontend_css_alter(&$css) {
  unset($css['sites/all/modules/contrib/views/css/views.css']);
  unset($css['sites/all/modules/contrib/date/date_api/date.css']);
}
