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

/**
 * Preprocess the primary entry level theme.
 */
function frontend_preprocess_panels_add_content_modal(&$vars) {

  // Now render the top level buttons (aka the root category) if any.
  $vars['root_content'] = '';
  $vars['fielded_pane_content'] = '';
  if (!empty($vars['categories'][t('fielded-panes')])) {
    foreach ($vars['categories'][t('fielded-panes')]['content'] as $content_type) {
      $vars['fielded_pane_content'] .= theme('panels_add_content_link', array(
        'renderer' => $vars['renderer'],
        'region' => $vars['region'],
        'content_type' => $content_type)
      );
    }

    // Unset categories link.
    foreach ($vars['categories_array'] as $key => $cat) {
      if (strpos($cat, $vars['categories'][t('fielded-panes')]['title'])) {
        unset($vars['categories_array'][$key]);
      }
    }
  }
  unset($vars['categories']['fielded-panes']);

  // Merge all items to others if only 1 exists.
  foreach ($vars['categories'] as $root_key => $category) {
    // Less then three items get merged in custom.
    if (count($category['content']) < 3) {
      foreach ($category['content'] as $content_type) {
        $vars['root_content'] .= theme('panels_add_content_link', array(
          'renderer' => $vars['renderer'],
          'region' => $vars['region'],
          'content_type' => $content_type)
        );
      }

      // Unset categories link.
      foreach ($vars['categories_array'] as $key => $cat) {
        if (strpos($cat, $category['title'])) {
          unset($vars['categories_array'][$key]);
        }
      }
      unset($vars['categories'][$root_key]);

      // In case no root item existed.
      if (empty($vars['categories']['root'])) {
        $vars['categories']['root'] = TRUE;
      }
    }
  }

  // Process the list of categories.
  foreach ($vars['categories'] as $key => $category_info) {
    // 'root' category is actually displayed under the categories, so
    // skip it.
    if ($key == 'root') {
      continue;
    }

    $class = 'panels-modal-add-category';
    if ($key == $vars['category']) {
      $class .= ' active';
    }

    $url = $vars['renderer']->get_url('select-content', $vars['region'], $key);
    $vars['categories_array'][] = ctools_ajax_text_button($category_info['title'], $url, '', $class);
  }

  // Now render the top level buttons (aka the root category) if any.
  if (!empty($vars['categories']['root'])) {
    foreach ($vars['categories']['root']['content'] as $content_type) {
      $vars['root_content'] .= theme('panels_add_content_link', array('renderer' => $vars['renderer'], 'region' => $vars['region'], 'content_type' => $content_type));
    }
  }
}
