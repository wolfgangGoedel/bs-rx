type t('a);

[@bs.send] external next : (t('a), 'a) => unit = "";
[@bs.send] external error : (t('a), 'e) => unit = "";
[@bs.send] external complete : t('a) => unit = "";