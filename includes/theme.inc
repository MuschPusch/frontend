<?php
/**
 * @file
 * theme.inc
 */

/**
 * Implements hook_theme().
 *
 * Return various tpl files.
 */
function frontend_theme($existing, $type, $theme, $path) {
  $theme_declaration = tcm_register_theme_functions($existing, $type, $theme, $path);
  return $theme_declaration;
}

/**
 * Implements hook_html_head_alter().
 *
 * Remove favicon.
 */
function frontend_html_head_alter(&$head_elements) {
  foreach ($head_elements as $key => $value) {
    if (!empty($value['#attributes']['rel']) && ($value['#attributes']['rel'] == 'shortcut icon')) {
      unset($head_elements[$key]);
    }
  }
}
