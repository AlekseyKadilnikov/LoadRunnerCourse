Action()
{

	lr_start_transaction("UC6_Itinerary");
	
	home_page();
	
	lr_think_time(11);

	login();
	
	lr_think_time(11);

	itinerary();
	
	lr_think_time(11);

	sign_off();
	
	lr_end_transaction("UC6_Itinerary",LR_AUTO);

	return 0;
}