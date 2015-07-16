<?php

$plugin = array(
  'title' => t('Info account login'),
  'description' => t('Displays a last logged in date.'),
  'single' => TRUE,
  'content_types' => array('info_login'),
  'render callback' => 'info_login_content_type_render',
  'edit form' => 'info_login_content_type_edit_form',
  'admin info' => 'info_login_content_type_admin_info',
  'category' => t('Drupal Camp CR'),
);

/**
 * Callback function to edit form.
 */
function info_login_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];
  $form['logged_message'] = array(
    '#type' => 'textfield',
    '#title' => t('Logged message'),
    '#description' => t('Custom logged message.'),
    '#default_value' => !empty($conf['logged_message']) ? $conf['logged_message'] : '',
  );
  return $form;
}

/**
 * Callback function to handle submission.
 */
function info_login_content_type_edit_form_submit($form, &$form_state) {
  foreach (array('logged_message') as $key) {
    $form_state['conf'][$key] = $form_state['values'][$key];
  }
}

/**
 * 'admin info' callback for panel pane.
 */
function info_login_content_type_admin_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass();
    $block->title = $conf['override_title'] ?
        $conf['override_title_text'] : 'Displays a last logged in date.';
    $custom_message = (!empty($conf['logged_message'])) ?
        ' and custom message ("@logged_message")' : '';
    $block->content = t("It will show: data of last logged in{$custom_message}.", array(
      '@logged_message' => $conf['logged_message'],
    ));
    return $block;
  }
}

/**
 * Callback function to render block.
 */
function info_login_content_type_render($subtype, $conf, $args, $context) {
  $block = new stdClass();
  $block->suject = t('Last logged');
  $block->content = theme('techs_users_last_logged_in', array('message' => $conf['logged_message']));
  return $block;
}
