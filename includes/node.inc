<?php

/**
 * @file
 * A collection of all node-related preprocess-functions.
 */

/**
 * Implements hook_preprocess_node().
 *
 * Add per content type tpl files.
 */
function frontend_preprocess_node(&$vars, $hook) {

  // Optionally, run node-type-specific preprocess functions, like
  // foo_preprocess_node_page() or foo_preprocess_node_story().
  $function = __FUNCTION__ . '_' . str_replace('-', '_', $vars['node']->type);
  if (function_exists($function)) {
    $function($vars, $hook);
  }
  if ($vars['view_mode'] != 'full') {
    $vars['theme_hook_suggestions'][] = 'node__' . $vars['view_mode'];
    $vars['theme_hook_suggestions'][] = 'node__' . $vars['node']->type . '__' . str_replace('-', '_', $vars['view_mode']);
  }
}
