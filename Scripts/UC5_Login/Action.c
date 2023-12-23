Action()
{
	lr_start_transaction("UC5_Login");
	
	home_page();
	
	lr_think_time(10);

	login();
	
	lr_think_time(10);

	flights_page();
	
	lr_think_time(10);
	
	search_flight();
	
	lr_think_time(10);

    sign_off();
	
	lr_end_transaction("UC5_Login",LR_AUTO);

	return 0;
}