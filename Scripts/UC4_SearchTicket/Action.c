Action()
{
	
	lr_start_transaction("UC4_SearchTicket");
	
	home_page();
	
	lr_think_time(5);

	login();
	
	lr_think_time(5);

	flights_page();
	
	lr_think_time(5);
	
	search_flight();
	
	lr_think_time(5);

	choose_ticket();
	
	lr_think_time(5);

	sign_off();
	
	lr_end_transaction("UC4_SearchTicket",LR_AUTO);

	return 0;
}