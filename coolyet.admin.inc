<?php
/**
 * @file coolyet.admin.inc
 * Settings for the CoolYet module.
 */

/**
 * Admin form.
 */
function coolyet_settings_form() {
  $form['coolyet_data'] = array(
    '#title' => t('Data URL'),
    '#type' => 'textfield',
    '#description' => t('The JSON data URL on the <a href="http://www.bom.gov.au/">Bureau of Meteorology</a> website. Find observations for your location, scroll to the bottom of the page and copy the <em>JavaScript Object Notation format (JSON) in row-major order</em> URL.'),
    '#default_value' => variable_get('coolyet_data', COOLYET_DATA),
  );
  $form['coolyet_change'] = array(
    '#title' => t('Cool Change'),
    '#type' => 'textfield',
    '#size' => 3,
    '#description' => t('The amount of &deg;C the temperature must drop in a 30 minute interval to cause a cool change to be declared.'),
    '#default_value' => abs(variable_get('coolyet_change', COOLYET_CHANGE)),
  );
  $form['coolyet_reset'] = array(
    '#title' => t('Status Reset'),
    '#type' => 'textfield',
    '#size' => 3,
    '#description' => t('The amount of &deg;C the temperature must rise in a 30 minute interval to cause the cool change status to reset to <em>FALSE</em>.'),
    '#default_value' => abs(variable_get('coolyet_reset', COOLYET_RESET)),
  );
  return system_settings_form($form);
}

/**
 * Validation for the settings form.
 */
function coolyet_settings_form_validate($form, &$form_state) {
  if (!valid_url($form_state['values']['coolyet_data'])) {
    form_set_error('coolyet_data', t('Enter a valid URL.'));
  }
  else  {
    $data = _coolyet_observations($form_state['values']['coolyet_data']);
    if (empty($data)) {
      form_set_error('coolyet_data', t('The URL must return valid JSON data.'));
    }
  }
  if (!is_numeric($form_state['values']['coolyet_change']) || (float)$form_state['values']['coolyet_change'] <= 0) {
    form_set_error('coolyet_change', t('The temperature difference must be a positive number.'));
  }
  if (!is_numeric($form_state['values']['coolyet_reset']) || (float)$form_state['values']['coolyet_reset'] <= 0) {
    form_set_error('coolyet_reset', t('The reset threshold must be a positive number.'));
  }

}
