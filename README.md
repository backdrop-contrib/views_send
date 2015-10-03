# Views Send

Project Views Send provides mass mailing using Views, enabling
a list of email addresses to be produced with a view and an
email to the group to be composed and sent.

The email messages are queued in a spool table and delivered 
only on cron.
You can control how many messages will be sent per cron run.

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