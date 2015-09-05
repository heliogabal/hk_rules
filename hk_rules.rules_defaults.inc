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
  $items['hk_expose_create_pdf_map_for_expose'] = entity_import('rules_config', '{ "hk_expose_create_pdf_map_for_expose" : {
      "LABEL" : "Create PDF map for Expos\\u00e9",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
      "TAGS" : [ "custom" ],
      "REQUIRES" : [ "rules", "rules_download" ],
      "USES VARIABLES" : { "node" : { "label" : "node", "type" : "node" } },
      "IF" : [
        { "entity_is_of_bundle" : {
            "entity" : [ "node" ],
            "type" : "node",
            "bundle" : { "value" : { "objekt" : "objekt" } }
          }
        },
        { "entity_has_field" : { "entity" : [ "node" ], "field" : "field_objekt_wkt" } }
      ],
      "DO" : [
        { "rules_download_action_generate_path" : {
            "USING" : {
              "path" : "printpdf\\/[site:current-page]",
              "cookie" : "1",
              "uri_scheme" : "public",
              "file_directory" : "exposekarten",
              "temporary" : "1"
            },
            "PROVIDE" : { "rules_download_file" : { "rules_downloaded_expose" : "Downloaded Expos\\u00e9" } }
          }
        },
        { "data_set" : {
            "data" : [ "node:field-apart-expose:file" ],
            "value" : [ "rules-downloaded-expose" ]
          }
        },
        { "entity_save" : { "data" : [ "node" ] } },
        { "drupal_message" : {
            "message" : "Expos\\u00e9 \\u003Ca href=\\u0022[rules-downloaded-expose:download-url]\\u0022\\u003E[rules-downloaded-expose:name]\\u003C\\/a\\u003E ist erstellt worden.",
            "repeat" : "0"
          }
        }
      ]
    }
  }');
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
        { "redirect" : { "url" : "\\/admin\\/content\\/dash\\/wohnungen", "destination" : "1" } }
      ]
    }
  }');
  $items['rules_create_corresponding_entity_reference_from_apartment'] = entity_import('rules_config', '{ "rules_create_corresponding_entity_reference_from_apartment" : {
      "LABEL" : "Create corresponding entity reference, when apartment has object",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "hk" ],
      "REQUIRES" : [ "rules" ],
      "ON" : {
        "node_insert--apartment" : { "bundle" : "apartment" },
        "node_update--apartment" : { "bundle" : "apartment" }
      },
      "IF" : [
        { "entity_has_field" : { "entity" : [ "node" ], "field" : "field_object_ref" } },
        { "entity_has_field" : {
            "entity" : [ "node:field-object-ref" ],
            "field" : "field_obj_apartments"
          }
        },
        { "entity_has_field" : { "entity" : [ "node" ], "field" : "title_field" } }
      ],
      "DO" : [
        { "list_add" : {
            "list" : [ "node:field-object-ref:field-obj-apartments" ],
            "item" : [ "node" ],
            "unique" : "1"
          }
        },
        { "entity_save" : { "data" : [ "node:field-object-ref" ], "immediate" : "1" } }
      ]
    }
  }');
  $items['rules_e_mail_to_client_and_office_when_inquiry_sent'] = entity_import('rules_config', '{ "rules_e_mail_to_client_and_office_when_inquiry_sent" : {
      "LABEL" : "E-Mail to client when inquiry sent",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "rules_i18n", "mimemail", "crm_core_activity" ],
      "REQUIRES" : [ "rules", "crm_core_activity" ],
      "ON" : { "crm_core_activity_insert" : [] },
      "IF" : [
        { "data_is" : { "data" : [ "crm-core-activity:type" ], "value" : "anfrage" } }
      ],
      "DO" : [
        { "mimemail" : {
            "key" : "[crm-core-activity:activity-id]",
            "to" : [ "crm-core-activity:field-activity-participants:1:primary-email" ],
            "subject" : "Ihre Anfrage zu [crm-core-activity:field-angefragte-wohnung]",
            "body" : "\\u003Cimg href=\\u0022http:\\/\\/hk.new.drupalforgood.eu\\/sites\\/all\\/themes\\/hk_theme\\/logo.png\\u0022 width=\\u0022165\\u0022 height=\\u002290\\u0022 alt=\\u0022Herbert+Kohlmeyer Immobilien GmbH Logo\\u0022 \\/\\u003E\\u003Cbr \\/\\u003E\\r\\n\\u003Ch4\\u003ESehr geehrte\\/r [crm-core-activity:field-activity-participants:1:contact_id],\\u003C\\/h4\\u003E\\r\\n\\r\\n\\u003Cp\\u003Evielen Dank f\\u00fcr Ihre Anfrage. Wir melden uns umgehend bei Ihnen mit weiteren Informationen. Anbei erhalten SIe bereits jetzt ein Informationsblatt zum neuen Widerrufsrecht und ihre Widerrufsbelehrung.\\u003C\\/p\\u003E\\r\\n\\r\\n\\u003Cp\\u003EIhr Herbert + Kohlmeyer Team\\u003C\\/p\\u003E",
            "plaintext" : "Hallo,\\r\\n\\r\\nvielen Dank f\\u00fcr Ihre Anfrage. Wir melden uns umgehend bei Ihnen mit weiteren Informationen. Anbei erhalten Sie bereits jetzt ein Informationsblatt zum neuen Widerrufsrecht und ihre Widerrufsbelehrung.\\r\\n\\r\\nIhr Herbert + Kohlmeyer Team",
            "attachments" : "sites\\/hk.new.drupalforgood.eu\\/files\\/hk_informationen_zur_widerrufsbelehrung.pdf\\r\\nsites\\/hk.new.drupalforgood.eu\\/files\\/hk_widerrufsbelehrung.pdf",
            "language" : "de"
          }
        }
      ]
    }
  }');
  $items['rules_e_mail_to_client_when_contact_form_sent'] = entity_import('rules_config', '{ "rules_e_mail_to_client_when_contact_form_sent" : {
      "LABEL" : "E-Mail to client when contact form sent",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "crm_core_activity" ],
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
      "REQUIRES" : [ "rules", "crm_core_activity" ],
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
      "REQUIRES" : [ "rules", "crm_core_activity" ],
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
      "ON" : { "node_presave--apartment" : { "bundle" : "apartment" } },
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
            "subject" : "[Website]: [node:title] ([node:field-objektid-nunumeric]-[node-unchanged:field-apart-no]) ist fertig zur Ver\\u00f6ffentlichung",
            "message" : "\\u0022[node:title] ([node:field-objektid-nunumeric]-[node-unchanged:field-apart-no])\\u0022 aus \\u0022[node:field-object-ref]\\u0022 ist von [node:author] zur Ver\\u00f6ffentlichung freigegeben worden. \\r\\n\\r\\nBitte bald \\u00fcberpr\\u00fcfen und ver\\u00f6ffentlichen!\\r\\n\\r\\nDirekter Link: [site:url]\\/node\\/[node:nid]"
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
  $items['rules_publish_object_when_apartment_is_published'] = entity_import('rules_config', '{ "rules_publish_object_when_apartment_is_published" : {
      "LABEL" : "Publish object, when apartment is published",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "node_presave--apartment" : { "bundle" : "apartment" } },
      "IF" : [
        { "entity_has_field" : { "entity" : [ "node" ], "field" : "field_save_workflow" } },
        { "entity_has_field" : { "entity" : [ "node" ], "field" : "field_object_ref" } },
        { "data_is" : { "data" : [ "node:field-save-workflow" ], "value" : "4" } },
        { "data_is" : { "data" : [ "node:field-object-ref:status" ], "value" : "0" } },
        { "entity_has_field" : {
            "entity" : [ "node:field_object_ref" ],
            "field" : "field_save_workflow"
          }
        }
      ],
      "DO" : [
        { "data_set" : { "data" : [ "node:field-object-ref:status" ], "value" : "1" } },
        { "data_set" : {
            "data" : [ "node:field-object-ref:field-save-workflow" ],
            "value" : "4"
          }
        }
      ]
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
  $items['rules_vbo_change_workflow_status'] = entity_import('rules_config', '{ "rules_vbo_change_workflow_status" : {
      "LABEL" : "VBO change workflow status to published",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "workflow_rules" ],
      "ACCESS_EXPOSED" : "1",
      "USES VARIABLES" : { "node" : { "label" : "node", "type" : "node" } },
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : { "apartment" : "apartment" } }
          }
        }
      ],
      "DO" : [
        { "workflowfield_field_set_state" : {
            "node" : [ "node" ],
            "field" : [ "node:field-save-workflow" ],
            "workflow_state" : { "value" : { "4" : "4" } },
            "workflow_comment" : "Mehrere Wohnungen ver\\u00f6ffentlicht."
          }
        }
      ]
    }
  }');
  $items['rules_vbo_change_workflow_status_to_archived'] = entity_import('rules_config', '{ "rules_vbo_change_workflow_status_to_archived" : {
      "LABEL" : "VBO change workflow status to archived",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "workflow_rules" ],
      "ACCESS_EXPOSED" : "1",
      "USES VARIABLES" : { "node" : { "label" : "node", "type" : "node" } },
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : { "apartment" : "apartment" } }
          }
        }
      ],
      "DO" : [
        { "workflowfield_field_set_state" : {
            "node" : [ "node" ],
            "field" : [ "node:field-save-workflow" ],
            "workflow_state" : { "value" : { "5" : "5" } },
            "workflow_comment" : "Mehrere Wohnungen ver\\u00f6ffentlicht."
          }
        }
      ]
    }
  }');
  $items['rules_vbo_change_workflow_status_to_ready'] = entity_import('rules_config', '{ "rules_vbo_change_workflow_status_to_ready" : {
      "LABEL" : "VBO change workflow status to ready",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "workflow_rules" ],
      "ACCESS_EXPOSED" : "1",
      "USES VARIABLES" : { "node" : { "label" : "node", "type" : "node" } },
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : { "apartment" : "apartment" } }
          }
        }
      ],
      "DO" : [
        { "workflowfield_field_set_state" : {
            "node" : [ "node" ],
            "field" : [ "node:field-save-workflow" ],
            "workflow_state" : { "value" : { "3" : "3" } },
            "workflow_comment" : "Mehrere Wohnungen ver\\u00f6ffentlicht."
          }
        }
      ]
    }
  }');
  $items['rules_vbo_change_workflow_status_to_sold'] = entity_import('rules_config', '{ "rules_vbo_change_workflow_status_to_sold" : {
      "LABEL" : "VBO change workflow status to sold",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "workflow_rules" ],
      "ACCESS_EXPOSED" : "1",
      "USES VARIABLES" : { "node" : { "label" : "node", "type" : "node" } },
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : { "apartment" : "apartment" } }
          }
        }
      ],
      "DO" : [
        { "workflowfield_field_set_state" : {
            "node" : [ "node" ],
            "field" : [ "node:field-save-workflow" ],
            "workflow_state" : { "value" : { "6" : "6" } },
            "workflow_comment" : "Mehrere Wohnungen ver\\u00f6ffentlicht."
          }
        }
      ]
    }
  }');
  return $items;
}
