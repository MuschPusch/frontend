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

  global $base_url;
  $vars['root_content'] = '';
  $vars['fielded_pane_content'] = '';

  $vars['layout_icon'] = $base_url . '/' . $vars['renderer']->display->allowed_layouts['frontpage']['path'] . '/' . $vars['renderer']->display->allowed_layouts['frontpage']['icon'];
  $vars['help'] = t('You are currently editing the %region region of the %layout layout. Please add new or existing content.', array('%region' => $vars['region'], '%layout' => $vars['renderer']->plugins['layout']['title']));

  dsm($vars);
  // Now render the top level buttons (aka the root category) if any.
  if (!empty($vars['categories'][t('fielded-panes')])) {
    sort($vars['categories'][t('fielded-panes')]['content']);
    foreach ($vars['categories'][t('fielded-panes')]['content'] as $content_type) {
      $vars['fielded_pane_content'] .= theme('panels_add_content_link', array(
        'renderer' => $vars['renderer'],
        'region' => $vars['region'],
        'content_type' => $content_type
      ));
    }

    // Unset categories link.
    foreach ($vars['categories_array'] as $key => $cat) {
      if (strpos($cat, $vars['categories'][t('fielded-panes')]['title'])) {
        unset($vars['categories_array'][$key]);
      }
    }
  }
  unset($vars['categories']['fielded-panes']);

  // Merge all items to others except fielded panes
  foreach ($vars['categories'] as $root_key => $category) {
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
      $vars['root_content'] .= theme('panels_add_content_link', array(
        'renderer' => $vars['renderer'],
        'region' => $vars['region'],
        'content_type' => $content_type)
      );
    }
  }
}

/**
 * Overwrites theme_panels_ipe_pane_wrapper().
 */
function frontend_panels_ipe_pane_wrapper($vars) {
  $output = $vars['output'];
  $pane = $vars['pane'];
  $display = $vars['display'];

  $attributes = array(
    'class' => 'panels-ipe-linkbar',
  );

  $type = ctools_get_content_type($pane->type);
  $title ='<span class = "panels-ipe-dragbar-admin-title">' . ctools_content_admin_title($type, $pane->subtype, $pane->configuration, $display->context) . '</span>';

  $links = theme('links', array('links' => $vars['links'], 'attributes' => $attributes));

  if (!empty($pane->locks['type']) && $pane->locks['type'] == 'immovable') {
    $links = '<div class="panels-ipe-dragbar panels-ipe-nodraghandle clearfix">' . $links .$title .'</div>';
  }
  else {
    $links = '<div class="panels-ipe-dragbar panels-ipe-draghandle clearfix">' . $links . $title . '<span class="panels-ipe-draghandle-icon"><span class="panels-ipe-draghandle-icon-inner"></span></span></div>';
  }

  $handlebar = '<div class="panels-ipe-handlebar-wrapper panels-ipe-on">' . $links . '</div>';

  return $handlebar . $output;
}


