<?php
/**
 * @file coolyet.pages.inc
 * Page handler for CoolYet.
 */

/**
 * Callback handler.
 *
 * Check recent temperature changes and spit out a user readable conclusion.
 *
 * @return
 *   A render array.
 */
function coolyet_melbourne() {
  $observations = _coolyet_observations();
  $cool = _coolyet_check($observations['data']);

  $state = $cool ? t('Yes') : t('No');

  // Link the URLs in the copyright notice.
  $copyright = strtr($observations['notice'][0]['copyright'], array(
    $observations['notice'][0]['copyright_url'] => l($observations['notice'][0]['copyright_url'], $observations['notice'][0]['copyright_url']),
    $observations['notice'][0]['disclaimer_url'] => l($observations['notice'][0]['disclaimer_url'], $observations['notice'][0]['disclaimer_url']),
    $observations['notice'][0]['feedback_url'] => l($observations['notice'][0]['feedback_url'], $observations['notice'][0]['feedback_url']),
  ));

  drupal_set_title(t('Has the @city cool change happened yet?', array('@city' => $observations['header'][0]['name'])));
dpm($observations);

  return array(
    'state' => array(
      '#type' => 'markup',
      '#markup' => $state,
      '#prefix' => '<div class="coolyet-state">',
      '#suffix' => '</div>',
    ),
    'information' => array(
      '#type' => 'markup',
      '#markup' => t('<a href="@url">Data</a> courtesy of Bureau of Meteorology. @name @product @issued. !copyright', array(
        '@url' => COOLYET_DATA,
        '@name' => $observations['header'][0]['name'],
        '@product' => $observations['header'][0]['product_name'],
        '@issued' => $observations['header'][0]['refresh_message'],
        '!copyright' => $copyright,
      )),
      '#prefix' => '<div class="coolyet-information">',
      '#suffix' => '</div>',
    ),
  );
}
