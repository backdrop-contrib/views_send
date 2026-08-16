# Changelog

All notable changes to Views Send for Backdrop CMS.

Releases before 1.x-1.2.0 are recorded in the tag list on GitHub; the Drupal
6/7 history that this module was ported from is in `CHANGELOG.txt`.

## 1.x-1.2.0 (unreleased)

First release since 1.x-1.1.7 (February 2017). It carries both the fixes made
for this release and the work committed between 2017 and 2025 that was never
tagged.

### Fixed

- Issue #20: removed `hook_update_last_removed()`. It returned a Drupal 6
  schema version, which made core treat every site as too old to update — the
  module was reported as "can not be updated" on update.php and then skipped
  for all future updates. Fix as proposed by jenlampton in pull request #21.
- Issue #18: the message body is no longer lost when returning to the message
  form from the preview with "Go back".
- Issue #22: the message body now opens in the text format configured for Mime
  Mail, which is the format Mime Mail applies when the message is sent, rather
  than always in the site's fallback format. Formats the sender may not use, or
  that no longer exist, still fall back.
- Issue #15: the "Default mail system" setting is now actually applied to each
  view display. It was being written to configuration and then overridden with
  Mime Mail on every send, so choosing anything else had no effect.
- Issue #17: documented the interaction between text formats and links in the
  message body in README.md.
- The mail spool expiration setting had no effect: the cron cleanup read the
  wrong configuration object, so every sent message was deleted on the next
  cron run whatever the setting said.
- The per-display mail system is no longer written to configuration on every
  single message, only when it changes.
- Added `hook_uninstall()` to remove the keys this module writes into
  `system.mail`. Its own configuration was already removed by core.
- `views_send_token_help` was registered with the Drupal 6 `arguments` key
  rather than `variables`.

### Changed

- `README.txt` has been folded into `README.md` and removed — its usage steps,
  module integration notes and developer hooks are now sections of the Markdown
  file, and its Drupal-only links have been dropped.
- The module description in `views_send.info` has been corrected, and
  `dependencies[] = views` added — Views was always required but never
  declared.

### Previously committed but never released

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
  naming convention.
