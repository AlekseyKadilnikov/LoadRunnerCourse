Action()
{
	lr_start_transaction("UC1_BuyTicket");
	
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
	
	payment_details();

	lr_think_time(5);

	itinerary();

	lr_end_transaction("UC1_BuyTicket",LR_AUTO);

	return 0;
}