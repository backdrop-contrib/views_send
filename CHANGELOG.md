# Changelog

All notable changes to Views Send for Backdrop CMS.

Releases before 1.x-1.2.0 are recorded in the tag list on GitHub; the Drupal
6/7 history that this module was ported from is in `CHANGELOG.txt`.

## 1.x-1.2.0 (unreleased)

First release since 1.x-1.1.7 (February 2017). The changes below were made
between 2017 and 2025 and have never been in a tagged release.

- Issue #18: the saved message body is now loaded back into the message field
  when values are remembered for a display.
- Issue #15: the mail system used for a view can be selected on the settings
  page, and `_views_send_mailsystem_set()` is applied per view display so a new
  view picks up Mime Mail.
- Issue #14: fixed the file attachment error under PHP 7.1 — `$attachments` is
  now always initialised before use.
- Issue #16: fixed the line spacing in the message field.
- Links to Mime Mail and Mandrill in the confirmation step now point at
  backdropcms.org rather than drupal.org.
- README rewritten for Backdrop, including the per-display Mime Mail template
  naming convention. `README.txt` has been folded into `README.md` and removed —
  its usage steps, module integration notes and developer hooks are now
  sections of the Markdown file, and its Drupal-only links have been dropped.
- The module description in `views_send.info` has been corrected, and
  `dependencies[] = views` added — Views was always required but never
  declared.
