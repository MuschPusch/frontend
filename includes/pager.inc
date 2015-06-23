<?php

/**
 * @file
 * Functions to aid in presenting database results as a set of pages.
 */

/**
 * Implements theme_pager().
 */
function frontend_pager($variables) {
  $tags = $variables['tags'];
  $element = $variables['element'];
  $parameters = $variables['parameters'];
  $quantity = $variables['quantity'];
  global $pager_page_array, $pager_total;

  //Utility classes
  $classes_pager_link = "Pager-link";
  $classes_pager_span = "Pager-span";

  // Calculate various markers within this pager piece:
  // Middle is used to "center" pages around the current page.
  $pager_middle = ceil($quantity / 2);
  // current is the page we are currently paged to
  $pager_current = $pager_page_array[$element] + 1;
  // first is the first page listed by this pager piece (re quantity)
  $pager_first = $pager_current - $pager_middle + 1;
  // last is the last page listed by this pager piece (re quantity)
  $pager_last = $pager_current + $quantity - $pager_middle;
  // max is the maximum page number
  $pager_max = $pager_total[$element];
  // End of marker calculations.

  // Prepare for generation loop.
  $i = $pager_first;
  if ($pager_last > $pager_max) {
    // Adjust "center" if at end of query.
    $i = $i + ($pager_max - $pager_last);
    $pager_last = $pager_max;
  }
  if ($i <= 0) {
    // Adjust "center" if at start of query.
    $pager_last = $pager_last + (1 - $i);
    $i = 1;
  }
  // End of generation loop preparation.

  $li_first = theme('pager_first', array(
    'text' => (isset($tags[0]) ? $tags[0] : t('« first')),
    'element' => $element,
    'parameters' => $parameters)
  );

  $li_previous = theme('pager_previous', array(
    'text' => (isset($tags[1]) ? $tags[1] : t('‹ previous')),
    'element' => $element,
    'interval' => 1,
    'parameters' => $parameters)
  );

  $li_next = theme('pager_next', array(
    'text' => (isset($tags[3]) ? $tags[3] : t('next ›')),
    'element' => $element,
    'interval' => 1,
    'parameters' => $parameters)
  );

  $li_last = theme('pager_last', array(
    'text' => (isset($tags[4]) ? $tags[4] : t('last »')),
    'element' => $element,
    'parameters' => $parameters)
  );

  if ($pager_total[$element] > 1) {
    if ($li_first) {
      $items[] = array(
        'class' => array(
          'Pager-item',
          'Pager-item--first'
        ),
        'data' => $li_first,
      );
    }
    if ($li_previous) {
      $items[] = array(
        'class' => array(
          'Pager-item',
          'Pager-item--previous'
        ),
        'data' => $li_previous,
      );
    }

    // When there is more than one page, create the pager list.
    if ($i != $pager_max) {
      if ($i > 1) {
        $items[] = array(
          'class' => array(
            'Pager-item',
            'Pager-item--ellipsis'
          ),
          'data' => _pager_span(array(
            'text' => '…',
            'attributes' => array(
              'class' => array(
                'Pager-span--ellipsis'
              )
            )
          )),
        );
      }
      // Now generate the actual pager piece.
      for (; $i <= $pager_last && $i <= $pager_max; $i++) {
        if ($i < $pager_current) {
          $items[] = array(
            'class' => array(
              'Pager-item'
            ),
            'data' => theme('pager_previous', array(
              'text' => $i,
              'element' => $element,
              'interval' => ($pager_current - $i),
              'parameters' => $parameters)),
          );
        }
        if ($i == $pager_current) {
          $items[] = array(
            'class' => array(
              'Pager-item'
            ),
            'data' => _pager_span(array(
              'text' => $i,
              'attributes' => array(
                'class' => array(
                  'is-current'
                )
              )
            )),
          );
        }
        if ($i > $pager_current) {
          $items[] = array(
            'class' => array(
              'Pager-item'
            ),
            'data' => theme('pager_next', array(
              'text' => $i,
              'element' => $element,
              'interval' => ($i - $pager_current),
              'parameters' => $parameters)),
          );
        }
      }
      if ($i < $pager_max) {
        $items[] = array(
          'class' => array(
            'Pager-item',
            'Pager-item--ellipsis'
          ),
          'data' => _pager_span(array(
            'text' => '…',
            'attributes' => array(
              'class' => array(
                'Pager-span--ellipsis'
              )
            )
          )),
        );
      }
    }
    // End generation.
    if ($li_next) {
      $items[] = array(
        'class' => array(
          'Pager-item',
          'Pager-item--next'
        ),
        'data' => $li_next,
      );
    }
    if ($li_last) {
      $items[] = array(
        'class' => array(
          'Pager-item',
          'Pager-item--last'
        ),
        'data' => $li_last,
      );
    }

    return '<h2 class="is-invisible">' . t('Pages') . '</h2>' . theme('item_list', array(
      'items' => $items,
      'attributes' => array(
        'class' => array(
          'Pager'
    ))));
  }
}

/**
 * Implements theme_pager_first().
 */
function frontend_pager_first($variables) {
  $text = $variables['text'];
  $element = $variables['element'];
  $parameters = $variables['parameters'];
  if(isset($variables['attributes'])) {
    $attributes = $variables['attributes'];
  }
  else {
    $attributes = '';
  }
  global $pager_page_array;
  $output = '';

  // If we are anywhere but the first page
  if ($pager_page_array[$element] > 0) {
    $output = theme('pager_link', array(
      'text' => $text,
      'page_new' => pager_load_array(0, $element, $pager_page_array),
      'element' => $element,
      'parameters' => $parameters,
      'attributes' => $attributes));
  }

  return $output;
}

/**
 * Implements theme_pager_previous().
 */
function frontend_pager_previous($variables) {
  $text = $variables['text'];
  $element = $variables['element'];
  $interval = $variables['interval'];
  $parameters = $variables['parameters'];
  if(isset($variables['attributes'])) {
    $attributes = $variables['attributes'];
  }
  else {
    $attributes = '';
  }
  global $pager_page_array;
  $output = '';

  // If we are anywhere but the first page
  if ($pager_page_array[$element] > 0) {
    $page_new = pager_load_array($pager_page_array[$element] - $interval, $element, $pager_page_array);

    // If the previous page is the first page, mark the link as such.
    if ($page_new[$element] == 0) {
      $output = theme('pager_first', array(
        'text' => $text,
        'element' => $element,
        'parameters' => $parameters,
        'attributes' => $attributes));
    }
    // The previous page is not the first page.
    else {
      $output = theme('pager_link', array(
        'text' => $text,
        'page_new' => $page_new,
        'element' => $element,
        'parameters' => $parameters,
        'attributes' => $attributes));
    }
  }

  return $output;
}

/**
 * Implements theme_pager_next().
 */
function frontend_pager_next($variables) {
  $text = $variables['text'];
  $element = $variables['element'];
  $interval = $variables['interval'];
  $parameters = $variables['parameters'];
  if(isset($variables['attributes'])) {
    $attributes = $variables['attributes'];
  }
  else {
    $attributes = '';
  }
  global $pager_page_array, $pager_total;
  $output = '';

  // If we are anywhere but the last page
  if ($pager_page_array[$element] < ($pager_total[$element] - 1)) {
    $page_new = pager_load_array($pager_page_array[$element] + $interval, $element, $pager_page_array);
    // If the next page is the last page, mark the link as such.
    if ($page_new[$element] == ($pager_total[$element] - 1)) {
      $output = theme('pager_last', array(
        'text' => $text,
        'element' => $element,
        'parameters' => $parameters,
        'attributes' => $attributes));
    }
    // The next page is not the last page.
    else {
      $output = theme('pager_link', array(
        'text' => $text,
        'page_new' => $page_new,
        'element' => $element,
        'parameters' => $parameters,
        'attributes' => $attributes));
    }
  }

  return $output;
}

/**
 * Implements theme_pager_last().
 */
function frontend_pager_last($variables) {
  $text = $variables['text'];
  $element = $variables['element'];
  $parameters = $variables['parameters'];
  if(isset($variables['attributes'])) {
    $attributes = $variables['attributes'];
  }
  else {
    $attributes = '';
  }
  global $pager_page_array, $pager_total;
  $output = '';

  // If we are anywhere but the last page
  if ($pager_page_array[$element] < ($pager_total[$element] - 1)) {
    $output = theme('pager_link', array(
      'text' => $text,
      'page_new' => pager_load_array($pager_total[$element] - 1, $element, $pager_page_array),
      'element' => $element,
      'parameters' => $parameters,
      'attributes' => $attributes));
  }

  return $output;
}

/**
 * Implements theme_pager_link().
 */
function frontend_pager_link($variables) {
  $text = $variables['text'];
  $page_new = $variables['page_new'];
  $element = $variables['element'];
  $parameters = $variables['parameters'];
  $attributes = $variables['attributes'];

  $page = isset($_GET['page']) ? $_GET['page'] : '';
  if ($new_page = implode(',', pager_load_array($page_new[$element], $element, explode(',', $page)))) {
    $parameters['page'] = $new_page;
  }

  $query = array();
  if (count($parameters)) {
    $query = drupal_get_query_parameters($parameters, array());
  }
  if ($query_pager = pager_get_query_parameters()) {
    $query = array_merge($query, $query_pager);
  }

  // Set each pager link title
  if (!isset($attributes['title'])) {
    static $titles = NULL;
    if (!isset($titles)) {
      $titles = array(
        t('« first') => t('Go to first page'),
        t('‹ previous') => t('Go to previous page'),
        t('next ›') => t('Go to next page'),
        t('last »') => t('Go to last page'),
      );
    }
    if (isset($titles[$text])) {
      $attributes['title'] = $titles[$text];
    }
    elseif (is_numeric($text)) {
      $attributes['title'] = t('Go to page @number', array('@number' => $text));
    }
  }

  // @todo l() cannot be used here, since it adds an 'active' class based on the
  //   path only (which is always the current path for pager links). Apparently,
  //   none of the pager links is active at any time - but it should still be
  //   possible to use l() here.
  // @see http://drupal.org/node/1410574
  $attributes['href'] = url($_GET['q'], array('query' => $query));

  $attributes['class'][] = 'Pager-link';

  return '<a' . drupal_attributes($attributes) . '>' . check_plain($text) . '</a>';
}

/**
 * Implements _pager_span().
 */
function _pager_span($variables) {
  $text = $variables['text'];
  $attributes = $variables['attributes'];

  $attributes['class'][] = 'Pager-span';

  return '<span' . drupal_attributes($attributes) . '>' . check_plain($text) . '</span>';
}

