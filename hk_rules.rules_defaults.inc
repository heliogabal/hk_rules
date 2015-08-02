<?php
/**
 * @file
 * hk_rules.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function hk_rules_default_rules_configuration() {
  $items = array();
  $items['hk_rules_after_login_redirect_translate_users_to_dash'] = entity_import('rules_config', '{ "hk_rules_after_login_redirect_translate_users_to_dash" : {
      "LABEL" : "After login redirect translate users to dash",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "custom" ],
      "REQUIRES" : [ "rules" ],
      "ON" : { "user_login" : [] },
      "IF" : [
        { "NOT text_matches" : {
            "text" : [ "site:current-page:path" ],
            "match" : "^user\\/reset",
            "operation" : "regex"
          }
        },
        { "user_has_role" : {
            "account" : [ "account" ],
            "roles" : { "value" : { "5" : "5" } },
            "operation" : "OR"
          }
        }
      ],
      "DO" : [ { "redirect" : { "url" : "translate" } } ]
    }
  }');
  $items['rules_after_login_redirect_admin_users_to_dashboard'] = entity_import('rules_config', '{ "rules_after_login_redirect_admin_users_to_dashboard" : {
      "LABEL" : "After login redirect admin users to dashboard",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "custom" ],
      "REQUIRES" : [ "rules" ],
      "ON" : { "user_login" : [] },
      "IF" : [
        { "NOT text_matches" : {
            "text" : [ "site:current-page:path" ],
            "match" : "^user\\/reset",
            "operation" : "regex"
          }
        },
        { "user_has_role" : {
            "account" : [ "account" ],
            "roles" : { "value" : { "3" : "3", "4" : "4", "7" : "7" } },
            "operation" : "OR"
          }
        }
      ],
      "DO" : [
        { "redirect" : { "url" : "\\/de\\/admin\\/content\\/dash", "destination" : "1" } }
      ]
    }
  }');
  $items['rules_e_mail_to_client_and_office_when_inquiry_sent'] = entity_import('rules_config', '{ "rules_e_mail_to_client_and_office_when_inquiry_sent" : {
      "LABEL" : "E-Mail to client when inquiry sent",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "rules_i18n", "crm_core_activity" ],
      "ON" : { "crm_core_activity_insert" : [] },
      "IF" : [
        { "data_is" : { "data" : [ "crm-core-activity:type" ], "value" : "anfrage" } }
      ],
      "DO" : [
        { "mail" : {
            "to" : [ "crm-core-activity:field-activity-participants:1:primary-email" ],
            "subject" : "Ihre Anfrage",
            "message" : "Sehr geehrte\\/r [crm-core-activity:field-activity-participants:0:contact_id],\\r\\n\\r\\nvielen Dank f\\u00fcr Ihre Anfrage. Wir melden uns umgehend bei Ihnen mit weiteren Informationen.\\r\\n\\r\\nIhr Herbert + Kohlmeyer Team",
            "language" : [ "site:current-user:language" ]
          }
        }
      ]
    }
  }');
  $items['rules_e_mail_to_client_when_contact_form_sent'] = entity_import('rules_config', '{ "rules_e_mail_to_client_when_contact_form_sent" : {
      "LABEL" : "E-Mail to client when contact form sent",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "rules_i18n", "crm_core_activity" ],
      "ON" : { "crm_core_activity_insert" : [] },
      "IF" : [
        { "data_is" : { "data" : [ "crm-core-activity:type" ], "value" : "kontaktformular" } }
      ],
      "DO" : [
        { "mail" : {
            "to" : [ "crm-core-activity:field-activity-participants:0:primary-email" ],
            "subject" : "Ihre Nachricht",
            "message" : "Hallo,\\r\\n\\r\\nvielen Dank f\\u00fcr Ihre Nachricht. Wir melden uns umgehend bei Ihnen mit weiteren Informationen.\\r\\n\\r\\nIhr Herbert + Kohlmeyer Team",
            "language" : [ "site:current-user:language" ]
          }
        }
      ]
    }
  }');
  $items['rules_e_mail_to_office_when_contact_form_sent'] = entity_import('rules_config', '{ "rules_e_mail_to_office_when_contact_form_sent" : {
      "LABEL" : "E-Mail to office when contact form sent",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "rules_i18n", "crm_core_activity" ],
      "ON" : { "crm_core_activity_insert" : [] },
      "IF" : [
        { "data_is" : { "data" : [ "crm-core-activity:type" ], "value" : "kontaktformular" } }
      ],
      "DO" : [
        { "mail" : {
            "to" : "rhalbmann@gmail.com",
            "subject" : "Neue Nachricht vom Kontaktformular",
            "message" : "Eine neue Nachricht ist \\u00fcber das Kontaktformular der Website eingetroffen. Bitte so schnell wie m\\u00f6glich bearbeiten!\\r\\n\\r\\nEingang der Anfrage: [crm-core-activity:created]\\r\\nNachricht: [crm-core-activity:field-activity-notes]\\r\\nName: [crm-core-activity:field-activity-participants]",
            "language" : [ "site:current-user:language" ]
          }
        }
      ]
    }
  }');
  $items['rules_e_mail_to_office_when_inquiry_sent'] = entity_import('rules_config', '{ "rules_e_mail_to_office_when_inquiry_sent" : {
      "LABEL" : "E-Mail to office when inquiry sent",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "rules_i18n", "crm_core_activity" ],
      "ON" : { "crm_core_activity_insert" : [] },
      "IF" : [
        { "data_is" : { "data" : [ "crm-core-activity:type" ], "value" : "anfrage" } }
      ],
      "DO" : [
        { "mail" : {
            "to" : [ "crm-core-activity:field-activity-participants:0:primary-email" ],
            "subject" : "Neue Anfrage",
            "message" : "Eine neue Anfrage ist eingetroffen. Bitte so schnell wie m\\u00f6glich bearbeiten!\\r\\n\\r\\nEingang der Anfrage: [crm-core-activity:created]\\r\\nWohnung: [crm-core-activity:field-angefragte-wohnung]\\r\\nName: [crm-core-activity:field-activity-participants]",
            "language" : [ "site:current-user:language" ]
          }
        }
      ]
    }
  }');
  $items['rules_e_mail_to_publisher_when_workflow_ready'] = entity_import('rules_config', '{ "rules_e_mail_to_publisher_when_workflow_ready" : {
      "LABEL" : "E-Mail to Publisher when workflow ready",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : {
        "node_presave--objekt" : { "bundle" : "objekt" },
        "node_presave--apartment" : { "bundle" : "apartment" }
      },
      "IF" : [
        { "NOT data_is" : {
            "data" : [ "node-unchanged:field-save-workflow" ],
            "op" : "IN",
            "value" : { "value" : { "3" : "3" } }
          }
        },
        { "data_is" : { "data" : [ "node:field-save-workflow" ], "value" : "3" } }
      ],
      "DO" : [
        { "mail_to_users_of_role" : {
            "roles" : { "value" : { "3" : "3" } },
            "subject" : "[Website]: [node:title] ist fertig zur Ver\\u00f6ffentlichung",
            "message" : "\\u0022[node:title]\\u0022 ist von [node:author] zur Ver\\u00f6ffentlichung freigegeben worden. \\r\\n\\r\\nBitte bald \\u00fcberpr\\u00fcfen und ver\\u00f6ffentlichen!\\r\\n\\r\\nDirekter Link: [site:url]\\/node\\/[node:nid]"
          }
        }
      ]
    }
  }');
  $items['rules_favoriten_anfrage'] = entity_import('rules_config', '{ "rules_favoriten_anfrage" : {
      "LABEL" : "Favoriten Anfrage",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
      "TAGS" : [ "custom" ],
      "REQUIRES" : [ "path", "rules" ],
      "IF" : [
        { "path_has_alias" : { "source" : "favoriten\\r\\n", "language" : "de" } },
        { "OR" : [] },
        { "path_has_alias" : { "source" : "favorites", "language" : "en" } }
      ],
      "DO" : [ { "views_rules_collect_rows" : [] } ]
    }
  }');
  $items['rules_kopiere_geodaten_vom_kiez_schattenobjekt'] = entity_import('rules_config', '{ "rules_kopiere_geodaten_vom_kiez_schattenobjekt" : {
      "LABEL" : "Kopiere Geodaten vom Kiez Schattenobjekt",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
      "TAGS" : [ "entity_rules_create" ],
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : {
        "entity" : { "label" : "Entity", "type" : "entity" },
        "continue" : { "label" : "Continue Rules", "type" : "boolean" }
      },
      "IF" : [
        { "entity_has_field" : { "entity" : [ "entity" ], "field" : "field_apart_kiez_schattenobjekt" } },
        { "NOT data_is_empty" : { "data" : [ "entity:field-apart-kiez-schattenobjekt" ] } },
        { "entity_has_field" : { "entity" : [ "entity" ], "field" : "field_apart_schattengebiet_wkt" } },
        { "entity_has_field" : {
            "entity" : [ "entity:field-apart-kiez-schattenobjekt" ],
            "field" : "field_kiez_gebiet_schattenobjekt"
          }
        }
      ],
      "DO" : [
        { "data_set" : {
            "data" : [ "entity:field-apart-schattengebiet-wkt" ],
            "value" : [
              "entity:field-apart-kiez-schattenobjekt:field-kiez-gebiet-schattenobjekt"
            ]
          }
        },
        { "entity_save" : { "data" : [ "entity" ] } }
      ],
      "PROVIDES VARIABLES" : [ "continue" ]
    }
  }');
  $items['rules_kopiere_geodaten_vom_kiez_schattenobjekt_update_'] = entity_import('rules_config', '{ "rules_kopiere_geodaten_vom_kiez_schattenobjekt_update_" : {
      "LABEL" : "Kopiere Geodaten vom Kiez Schattenobjekt (update)",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
      "TAGS" : [ "entity_rules_update" ],
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : {
        "entity" : { "label" : "Entity", "type" : "entity" },
        "continue" : { "label" : "Continue Rules", "type" : "boolean" }
      },
      "IF" : [
        { "entity_has_field" : { "entity" : [ "entity" ], "field" : "field_apart_kiez_schattenobjekt" } },
        { "NOT data_is_empty" : { "data" : [ "entity:field-apart-kiez-schattenobjekt" ] } },
        { "entity_has_field" : {
            "entity" : [ "entity:field-apart-kiez-schattenobjekt" ],
            "field" : "field_kiez_gebiet_schattenobjekt"
          }
        },
        { "entity_has_field" : {
            "entity" : [ "entity:field-apart-kiez-schattenobjekt" ],
            "field" : "field_kiez_gebiet_schattenobjekt"
          }
        },
        { "entity_has_field" : { "entity" : [ "entity" ], "field" : "field_apart_schattengebiet_wkt" } }
      ],
      "DO" : [
        { "data_set" : {
            "data" : [ "entity:field-apart-schattengebiet-wkt" ],
            "value" : [
              "entity:field-apart-kiez-schattenobjekt:field-kiez-gebiet-schattenobjekt"
            ]
          }
        },
        { "entity_save" : { "data" : [ "entity" ] } }
      ],
      "PROVIDES VARIABLES" : [ "continue" ]
    }
  }');
  $items['rules_publish_content_when_workflow_state_active'] = entity_import('rules_config', '{ "rules_publish_content_when_workflow_state_active" : {
      "LABEL" : "Publish content when workflow state active",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : {
        "node_presave--objekt" : { "bundle" : "objekt" },
        "node_presave--apartment" : { "bundle" : "apartment" }
      },
      "IF" : [
        { "data_is" : { "data" : [ "node:field-save-workflow" ], "value" : "4" } }
      ],
      "DO" : [ { "node_publish" : { "node" : [ "node" ] } } ]
    }
  }');
  $items['rules_unpublish_content_when_workflow_state_is_not_active'] = entity_import('rules_config', '{ "rules_unpublish_content_when_workflow_state_is_not_active" : {
      "LABEL" : "Unpublish content when workflow state is not active",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : {
        "node_presave--objekt" : { "bundle" : "objekt" },
        "node_presave--apartment" : { "bundle" : "apartment" }
      },
      "IF" : [
        { "NOT data_is" : { "data" : [ "node:field-save-workflow" ], "value" : "4" } }
      ],
      "DO" : [ { "node_unpublish" : { "node" : [ "node" ] } } ]
    }
  }');
  return $items;
}
