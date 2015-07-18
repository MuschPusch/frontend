<?php
/**
 * @file
 * Provides preprocess logic and other functionality for theming.
 */

// Ensure that __DIR__ constant is defined:
if (!defined('__DIR__')) {
  define('__DIR__', dirname(__FILE__));
}

// Require files:
require_once __DIR__ . '/includes/helpers.inc';
require_once __DIR__ . '/includes/menus.inc';
require_once __DIR__ . '/includes/pager.inc';
require_once __DIR__ . '/includes/theme.inc';
require_once __DIR__ . '/includes/node.inc';
require_once __DIR__ . '/includes/forms.inc';
require_once __DIR__ . '/includes/field.inc';


function frontend_fedit($content, $entity_type, $entity_bundle, $entity_id, $name, $html) {
  $output = is_array($content) ? drupal_render($content) : $content;
  if (!user_access('access fedit')) {
    return $output;
  }
  $data = fedit_helper_generate_data($entity_type, $entity_bundle, $entity_id, $name, $html);

  return theme('fedit_wrap', array(
    'content' => $content,
    'data' => $data
  ));
}

