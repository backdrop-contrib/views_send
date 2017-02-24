<?php

/**
 * @file
 *   Views Send administration page.
 *
 * @ingroup views_send
 */

/**
 * Callback for admin/settings/views_send menu item.
 */
function views_send_settings() {
  $form = array();
  if (VIEWS_SEND_MIMEMAIL) {
    $form['views_send_attachment_valid_extensions'] = array(
      '#type' => 'textfield',
      '#title' => t('Valid file extensions for attachments'),
      '#default_value' => config_get('views_send.settings','views_send_attachment_valid_extensions'),
      '#description' => t('A space separated list of allowed file extensions for attachments. Leave the list empty if you want to use the default list from file_save_upload().'),
    );
  }
  $throttle = backdrop_map_assoc(array(1, 10, 20, 30, 50, 100, 200, 500, 1000, 2000, 5000, 10000, 20000));
  $throttle[0] = t('Unlimited');

  $form['views_send_throttle'] = array(
    '#type' => 'select',
    '#title' => t('Cron throttle'),
    '#options' => $throttle,
    '#default_value' => config_get('views_send.settings','views_send_throttle'),
    '#description' => t('Sets the numbers of messages sent per cron run. Failure to send will also be counted. Cron execution must not exceed the PHP maximum execution time of %max seconds. You find the time spend to send emails in the !recent_logs.', array('%max' => ini_get('max_execution_time'), '!recent_logs' => l(t('Recent log entries'), 'admin/reports/dblog'))),
  );
  $form['views_send_spool_expire'] = array(
    '#type' => 'select',
    '#title' => t('Mail spool expiration'),
    '#options' => array(0 => t('Immediate'), 1 => t('1 day'), 7 => t('1 week'), 14 => t('2 weeks')),
    '#default_value' => config_get('views_send.settings','views_send_spool_expire'),
    '#description' => t('Emails are spooled. How long must messages be retained in the spool after successfull sending.'),
  );
  $form['views_send_debug'] = array(
    '#type' => 'checkbox',
    '#title' => t('Log emails'),
    '#default_value' => config_get('views_send.settings','views_send_debug'),
    '#description' => t('When checked all outgoing messages are logged in the system log. A logged email does not guarantee that it is sent or will be delivered. It only indicates that a message is sent to the PHP mail() function. No status information is available of delivery by the PHP mail() function.'),
  );
	$form['views_send_additional_options'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show additional email options'),
    '#default_value' => config_get('views_send.settings','views_send_additional_options'),
    '#description' => t('When checked the user will be able to use the additional email options.'),
  );
  $form['views_send_from_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Send from name'),
    '#default_value' => config_get('views_send.settings','views_send_from_name'),
    '#description' => t('The name to be shown as the sender of the email.'),
  );
  $form['views_send_from_mail'] = array(
    '#type' => 'textfield',
    '#title' => t('Send from email address'),
    '#default_value' => config_get('views_send.settings','views_send_from_mail'),
    '#description' => t('The email address to be shown as the sender of the email.'),
  );

  // Add a submit button
  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return $form;
}

/**
 * Submit handler for module_settings_form().
 */
function views_send_settings_submit($form, &$form_state){
  $config = config('views_send.settings');
  $config->set('views_send_throttle', $form_state['values']['views_send_throttle']);
  $config->set('views_send_spool_expire', $form_state['values']['views_send_spool_expire']);
  $config->set('views_send_debug', $form_state['values']['views_send_debug']);
  $config->set('views_send_additional_options', $form_state['values']['views_send_additional_options']);
  $config->set('views_send_from_name', $form_state['values']['views_send_from_name']);
  $config->set('views_send_from_mail', $form_state['values']['views_send_from_mail']);
  $config->save();
  backdrop_set_message(t('The configuration options have been saved.'));
}
