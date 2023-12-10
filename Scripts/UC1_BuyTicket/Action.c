Action()
{
	lr_start_transaction("UC1_BuyTicket");

	lr_start_transaction("home_page");
	
	home_page();

	lr_end_transaction("home_page",LR_AUTO);
	
	lr_think_time(2.5);
	
	lr_start_transaction("login");

	login();
	
	lr_end_transaction("login",LR_AUTO);
	
	lr_think_time(2.5);

	lr_start_transaction("flights_page");

	flights_page();
	
	lr_end_transaction("flights_page",LR_AUTO);
	
	lr_think_time(2.5);

	lr_start_transaction("search_flight");
	
	search_flight(atoi(lr_eval_string("{numPassengers}")));
	
	lr_end_transaction("search_flight",LR_AUTO);
	
	lr_think_time(2.5);

	lr_start_transaction("choose_ticket");

	choose_ticket();

	lr_end_transaction("choose_ticket",LR_AUTO);
	
	lr_think_time(2.5);

	lr_start_transaction("payment_details");
	
	payment_details(atoi(lr_eval_string("{numPassengers}")));

	lr_end_transaction("payment_details",LR_AUTO);
	
	lr_think_time(2.5);

	lr_start_transaction("itinerary");

	itinerary();

	lr_end_transaction("itinerary",LR_AUTO);
	
	lr_end_transaction("UC1_BuyTicket",LR_AUTO);

	return 0;
}