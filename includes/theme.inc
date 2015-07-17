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
  return array(
  );
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

/**
 * Implements theme_preprocess_search_result().
 */
function frontend_preprocess_search_result(&$vars) {
  $result = $vars['result'];
  $node = $result['node'];
  $vars['rendered_node'] = node_view($node, 'search_result');
}

/**
 * Implementation of hook_preprocess_html().
 */
function frontend_preprocess_html() {
  global $user;
  if ($user->uid > 0) {
    drupal_add_css(drupal_get_path('theme', 'frontend') . '/assets/stylesheets/application.css', array('group' => CSS_THEME, 'every_page' => TRUE));
    $settings = array(
      'CToolsModal' => array(
        'loadingText' => t('Loading...'),
        'closeText' => t('Close Window'),
        'closeImage' => theme('image', array(
          'path' => ctools_image_path('icon-close-window.png'),
          'title' => t('Close window'),
          'alt' => t('Close window'),
        )),
        'throbber' => theme('image', array(
            'path' => ctools_image_path('throbber.gif'),
            'title' => t('Loading...'),
            'alt' => t('Loading'),
          )),
        'modalSize' => array(
          'type' => 'scale',
          'width' => .8,
          'height' => .8,
          'addWidth' => 0,
          'addHeight' => 0,
          'contentRight' => 45,
          'contentBottom' => 75
        ),
      ),
    );
    drupal_add_js($settings, 'setting');
  }
}
