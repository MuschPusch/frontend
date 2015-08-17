<?php
/**
 * @file
 * Panels / FPP specific code.
 */


/**
 * Create preprocess functions per fieldable panel pane.
 */
function frontend_preprocess_fieldable_panels_pane(&$vars) {
  global $theme;
  $fn = $theme . '_preprocess_fieldable_panels_pane_' . $vars['elements']['#bundle'];
  if (function_exists($fn)) {
    $fn($vars);
  }
  $view_mode = $vars['elements']['#view_mode'];
  if ($view_mode != 'full') {
    $vars['theme_hook_suggestions'][] = 'fieldable_panels_pane____' . $view_mode;
    $vars['theme_hook_suggestions'][] = 'fieldable_panels_pane__' . str_replace('-', '_', $vars['elements']['#bundle']) . '__' . str_replace('-', '_', $view_mode);
  }
}
