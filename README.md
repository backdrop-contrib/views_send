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

## Templates

This latest release of Views Send for Backdrop provides for customised
templates for specific views. If, for example, your create a view with
machine name test_views_send_page_2, you can create a variant of the basic
Mimemail template mimemail-message.tpl.php and name a modified version
mimemail-message--views-send--test-views-send-page-2.tpl.php,
note the use of hyphens in place of underscores, and double hyphens
in some situations. This variant template should be stored in your site's
theme folder.


## Help & Documentation</h2>

See readme.txt for more information about installation and use.


## License

This project is GPL v2 software. See the LICENSE.txt file in this directory for complete text.
    
        
## Current Maintainer for Backdrop

Graham Oliver (github.com/Graham-72/)

## Credits

### Maintainer for Drupal:

- hansfn - Hans Fredrik Nordhaug

### Acknowledgement

This port to Backdrop would not, of course, be possible without all
the work done by the developers and maintainers of the Drupal module.

The Drupal 6 version of this module was sponsored by Grafit SRL, 
now Webikon | http://www.webikon.com
