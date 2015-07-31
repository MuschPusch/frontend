<?php

/**
 * Implements theme_preprocess().
 */
function frontend_preprocess_panels_default_style_render_region(&$vars) {
  $display = $vars['display'];
  $vars['theme_hook_suggestions'][] = 'panels_default_style_render_region';
  $vars['theme_hook_suggestions'][] = 'panels_default_style_render_region__' . $display->layout;
  $vars['theme_hook_suggestions'][] = 'panels_default_style_render_region__' . $display->layout . '__' . $vars['region_id'];
}

/**
 * Implements hook_preprocess().
 *
 * Inject panels-context into fpp-entity.
 */
function frontend_preprocess_panels_pane(&$vars) {
  if (!empty($vars['content']['#fieldable_panels_pane'])) {
    $region = FALSE;
    foreach ($vars['display']->panels as $key => $content) {
      if (in_array($vars['pane']->pid, $content)) {
        $region = $key;
      }
    }
    $vars['content']['#fieldable_panels_pane']->panels_context = array(
      'layout' => $vars['display']->layout,
      'region' => $region
    );
  }
}
