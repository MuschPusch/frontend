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
