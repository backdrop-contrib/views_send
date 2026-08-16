# Views Send

Project Views Send provides mass mailing using Views, enabling
a list of email addresses to be produced as part of a view and
an email to the group to be composed and sent.

The email messages can be sent immediately or can be queued in
a spool table and delivered only on cron.
You can control how many messages will be sent per cron run.

Messages can be prepared in HTML form using Backdrop's
WYSIWYG editor and then sent by using the separate
Mime Mail module. Such an email can include images and also
an attached file.

This is a port from the Drupal module of the same name.


## Installation

- Install this module using the official Backdrop CMS instructions at
  https://backdropcms.org/guide/modules.

- Use the configuration page at /admin/config/system/views_send to
  set values for:
  + cron throttle
  + mail spool expiration
  + log emails (on or off)
  + send from name
  + send from email address
  + default mail system


## Usage

1. Create a view and add at least one column containing email addresses.
2. [Optional] Expose Views filters so that the list of recipients can be
   built from the page itself.
3. Add the "Global: Send email" field to your view. This field provides the
   checkboxes that allow multiple rows to be selected.
4. Save the view and load the page. Use any exposed filters to build the list,
   select all or some of the rows, and press "Prepare email".
5. Fill in the message form to configure the email. Tokens can be used to
   personalise both the subject and the body. A message you send regularly can
   be saved as a template and loaded again next time - see "Saved message
   templates" below.
6. Preview the message and send it.

Permissions are set at Administration > People > Permissions:
"Send mass mail with Views" is required to send anything at all,
"Use attachments with Views Send" to attach files, and
"Administer mass mail with Views" for the settings page.


## Integration with other modules

- **Mime Mail** — when enabled, messages can be sent as rich HTML and files can
  be attached. Without it, all messages are converted to plain text.
  Mandrill, Swift Mailer, and HTML Mail together with Mime Mail are recognised
  as alternative providers of the same capability.
- **Token** — the general token tree is offered in the message form. Note that
  the row-based tokens for the view's own fields are always available, whether
  or not Token is enabled.
- **Rules** — three events are provided: after an individual email is sent,
  after an individual email is added to the spool, and after all emails have
  been added to the spool.


## Scope and sending limits

**Views Send is not designed for mass mailing.** It is meant for sending to a
modest list produced by a view — a committee, a working group, a handful of
members. Sending newsletters or other bulk email with it is at your own risk.

Every hosting provider limits how much mail an account may send. The limits
differ between providers, and between sending methods on the same provider:
mail sent by PHP from a web server is often capped far lower than mail sent
through authenticated SMTP, and a newly created mailbox is frequently
restricted for its first days. They are usually several separate caps —
messages per day, total recipients per day, unique recipients per day, and a
maximum number of addresses on any single message.

Exceeding them can have messages throttled, silently dropped or treated as
spam, and repeated breaches can put the sending account, or the whole hosting
account, at risk.

Check with your provider before sending in bulk, and use a dedicated email
marketing service for newsletters — those handle consent, unsubscribes and
delivery reputation, which this module does not.

## Text formats

The message body is composed in whichever text format Mime Mail is configured
to use (Administration > Configuration > Media > Mime Mail), since that is the
format Mime Mail will apply to the body when the message is sent. Composing in
one format and sending in another is what produces most "it looked right in the
preview" reports.

Filters that rewrite links are worth checking before you rely on them. An email
address typed into the body of a message can come out as something other than a
working mailto: link, depending on which filters the chosen format runs. If you
need addresses in the body, use a text format with a minimal filter set.

## Saved message templates

A message you send regularly does not have to be retyped. On the message form,
"Save as template" keeps the sender, subject and body under a name of your
choosing; "Load a saved template" fills the form back in from it. Saving under
the name of an existing template replaces it, so loading a template, editing it
and saving it again updates it in place.

Templates are saved when you press Next, whether or not you go on to send, so
writing one is not a commitment to a mailing.

Templates are shared by every view on the site. That makes a message written
once reusable anywhere, but it also means a body containing tokens such as
`[views-send-field_surname]` will leave those tokens unreplaced on a view whose
fields differ. The view each template was saved from is recorded and shown at
Administration > Configuration > System > Views Send > Templates, where
templates can also be deleted.

Deliberately **not** saved in a template are the "Field used for recipient's
name" and "Field used for recipient's email" selections. A field name from one
view means nothing in another. Those stay with the "Remember these values"
checkbox, which is separate: it remembers the whole form, including the
recipient fields, for the one view display you are on.

Each template is stored as its own configuration file
(`views_send.template.<name>.json`), so templates can be exported and deployed
between sites like any other Backdrop configuration.


## Mime Mail theme templates

Views Send for Backdrop provides for customised templates for specific views.
If, for example, you create a view with machine name test_views_send_page_2,
you can create a variant of the basic Mimemail template mimemail-message.tpl.php
and name a modified version
mimemail-message--views-send--test-views-send-page-2.tpl.php,
note the use of hyphens in place of underscores, and double hyphens
in some situations. This variant template should be stored in your site's
theme folder.


## For developers

The module provides two hooks:

- `hook_views_send_mail_queued($message, $view, $row_id)`
  Called just after each message is queued.
- `hook_views_send_mail_alter(&$message)`
  Called just before each message is queued. Setting `$message['send']` to
  FALSE cancels that message.


## Help & Documentation

Additional documentation is located in the Wiki: https://github.com/backdrop-contrib/views_send/wiki

## Issues:
Bugs and Feature requests should be reported in the Issue Queue: https://github.com/backdrop-contrib/views_send/issues

## License

This project is GPL v2 software. See the LICENSE.txt file in this directory for complete text.


## Current Maintainer for Backdrop
- [Steve Moorhouse (albanycomputers)](https://github.com/albanycomputers)
- Seeking additional maintainers and contributors.

## Credits

### Sponsorship:
- [Albany Computer Services](https://www.albany-computers.co.uk)
- [Albany Web Design](https://www.albanywebdesign.co.uk)
- [Albany Hosting](https://www.albany-hosting.co.uk)

### Past Maintainers

- Graham Oliver (github.com/Graham-72/)

### Maintainers for Drupal:

- hansfn - Hans Fredrik Nordhaug
- Claudiu Cristea (claudiu.cristea) - author of the original Drupal 6 version

### Acknowledgement

This port to Backdrop would not, of course, be possible without all
the work done by the developers and maintainers of the Drupal module.

The Drupal 6 version of this module was sponsored by Grafit SRL,
now Webikon | http://www.webikon.com
