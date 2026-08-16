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

  $form['scope'] = array(
    '#type' => 'help',
    '#markup' => t('<strong>Views Send is not designed for mass mailing.</strong> It is meant for sending to a modest list produced by a view - a committee, a working group, a handful of members. Sending newsletters or other bulk email with it is at your own risk. Every hosting provider limits how much mail an account may send, the limits differ between providers and between sending methods, and exceeding them can have your messages dropped, marked as spam, or your account suspended. Check with your provider before sending in bulk, and use a dedicated email marketing service for newsletters.'),
  );

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

  // Add default mail system
  $mailsystem_options = array();
  $mailsystem_options['DefaultMailSystem'] = 'Default for System';
  if (VIEWS_SEND_MIMEMAIL) {
    $mailsystem_options['MimeMailSystem'] = 'Mime Mail';
  }

  $form['views_send_default_mailsystem'] = array(
    '#type' => 'select',
    '#options' => $mailsystem_options,
    '#title' => t('Default mail system'),
    '#default_value' => config_get('views_send.settings','views_send_default_mailsystem'),
    '#description' => t('The default mail system to be used for Views Send messages.'),
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
 * Page callback: lists the saved message templates.
 *
 * Templates are created from a view's message form, not here - this page
 * exists so they can be reviewed and removed, which config objects otherwise
 * make invisible.
 */
function views_send_templates_page() {
  $rows = array();
  foreach (views_send_template_load_all() as $name => $template) {
    $rows[] = array(
      check_plain($template['label']),
      check_plain($template['subject']),
      $template['source_display'] ? check_plain($template['source_display']) : t('Unknown'),
      l(t('Delete'), 'admin/config/system/views_send/templates/' . $name . '/delete'),
    );
  }

  $build['help'] = array(
    '#type' => 'help',
    '#markup' => t('Templates are saved from the message form of a view, using the "Save as template" field, and are then offered on every view. A message written for one view may contain tokens another view cannot replace, so the view each template was saved from is shown here.'),
  );
  $build['templates'] = array(
    '#theme' => 'table',
    '#header' => array(t('Name'), t('Subject'), t('Saved from'), t('Operations')),
    '#rows' => $rows,
    '#empty' => t('No templates have been saved yet.'),
  );

  return $build;
}

/**
 * Form callback: asks for confirmation before deleting a template.
 *
 * @param string $name
 *   The machine name of the template to delete.
 */
function views_send_template_delete_form($form, &$form_state, $name) {
  $template = views_send_template_load($name);
  if (!$template) {
    return MENU_NOT_FOUND;
  }

  $form['name'] = array(
    '#type' => 'value',
    '#value' => $name,
  );
  $form['label'] = array(
    '#type' => 'value',
    '#value' => $template['label'],
  );

  return confirm_form($form,
    t('Delete the template %label?', array('%label' => $template['label'])),
    'admin/config/system/views_send/templates',
    t('This cannot be undone. Messages already sent or waiting in the spool are not affected.'),
    t('Delete')
  );
}

/**
 * Submit handler for views_send_template_delete_form().
 */
function views_send_template_delete_form_submit($form, &$form_state) {
  views_send_template_delete($form_state['values']['name']);
  backdrop_set_message(t('Deleted the template %label.', array('%label' => $form_state['values']['label'])));
  $form_state['redirect'] = 'admin/config/system/views_send/templates';
}

/**
 * Submit handler for module_settings_form().
 */
function views_send_settings_submit($form, &$form_state){
  $config = config('views_send.settings');
  $config->set('views_send_attachment_valid_extensions', $form_state['values']['views_send_attachment_valid_extensions']);
  $config->set('views_send_throttle', $form_state['values']['views_send_throttle']);
  $config->set('views_send_spool_expire', $form_state['values']['views_send_spool_expire']);
  $config->set('views_send_debug', $form_state['values']['views_send_debug']);
  $config->set('views_send_additional_options', $form_state['values']['views_send_additional_options']);
  $config->set('views_send_from_name', $form_state['values']['views_send_from_name']);
  $config->set('views_send_from_mail', $form_state['values']['views_send_from_mail']);
  $config->set('views_send_default_mailsystem', $form_state['values']['views_send_default_mailsystem']);
  $config->save();

  config_set('system.mail','views_send', $form_state['values']['views_send_default_mailsystem']);

  backdrop_set_message(t('The configuration options have been saved.'));
}
