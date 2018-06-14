type t('a);

[@bs.module "rxjs"] [@bs.new] external make : unit => t('a) = "Subject";

external asObservable : t('a) => Rx_Observable.t('a) = "%identity";

external asObserver : t('a) => Rx_Observer.t('a) = "%identity";