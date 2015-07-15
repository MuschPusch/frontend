<?php
/**
 * @file
 * FPP spefic code.
 */

/**
 * Create preprocess functions per fieldable panel pane.
 */
function frontend_preprocess_fieldable_panels_pane(&$vars) {
  global $theme;
  $fn = $theme . '_preprocess_fieldable_panels_pane_' . $vars['elements']['#bundle'];
  if (isset($vars['content']['title'])) {
    unset($vars['content']['title']);
  }
  if (function_exists($fn)) {
    $fn($vars);
  }
}
