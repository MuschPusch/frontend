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
}
