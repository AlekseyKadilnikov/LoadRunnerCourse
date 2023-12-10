Action()
{
	
	lr_start_transaction("UC4_SearchTicket");

	lr_start_transaction("home_page");
	
	home_page();

	lr_end_transaction("home_page",LR_AUTO);
	
	lr_think_time(3);
	
	lr_start_transaction("login");

	login();
	
	lr_end_transaction("login",LR_AUTO);
	
	lr_think_time(3);

	lr_start_transaction("flights_page");

	flights_page();

	lr_end_transaction("flights_page",LR_AUTO);
	
	lr_think_time(3);

	lr_start_transaction("search_flight");
	
	search_flight(1);
	
	lr_end_transaction("search_flight",LR_AUTO);
	
	lr_think_time(3);

	lr_start_transaction("choose_ticket");

	choose_ticket();

	lr_end_transaction("choose_ticket",LR_AUTO);
	
	lr_think_time(3);

	lr_start_transaction("sign_off");

	sign_off();

	lr_end_transaction("sign_off",LR_AUTO);
	
	lr_end_transaction("UC4_SearchTicket",LR_AUTO);

	return 0;
}