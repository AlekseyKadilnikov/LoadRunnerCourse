Action()
{
	int flight_count_before_remove;
	int flight_count_after_remove;
	int removed_flights_count;
	int flight_count_to_be_left;
	char cancel_flights_body[16384];
	char* max_random_flights_number_to_remove_string;
	int i, j;
	int max_random_flights_number_to_remove;
	int random_flights_number_to_remove;
	
	lr_start_transaction("UC2_RemoveTicket");

	home_page();
	
	lr_think_time(5);

	login();
	
	lr_think_time(5);
	
	web_reg_save_param_ex(
		"ParamName=flightID",
		"LB=flightID\" value=\"",
		"RB=\"  />",
		"NotFound=warning",
		"Ordinal=All",
		LAST);
	
	itinerary();
	
	lr_think_time(5);

	strcpy(cancel_flights_body, "");
	
	flight_count_before_remove = atoi(lr_eval_string("{flightID_count}"));
	
	if(flight_count_before_remove != 0) {
		
		lr_start_transaction("remove_ticket");

		web_add_header("Origin", 
			"{protocol}://{host}:{port}");
	
		web_add_auto_header("Sec-Fetch-User", 
			"?1");
		
		srand(time(NULL));
		max_random_flights_number_to_remove = atoi(lr_eval_string("{MaxRandomValue}"));
		
		if(flight_count_before_remove > max_random_flights_number_to_remove) {
			random_flights_number_to_remove = 1 + rand()%(max_random_flights_number_to_remove - 1 + 1);
		}
		else {
			random_flights_number_to_remove = 1 + rand()%(flight_count_before_remove - 1 + 1);
		}
		
		for (i=1; i<=random_flights_number_to_remove; i++)
		{
			lr_save_int(i,"flightIndex");
			strcat(cancel_flights_body, lr_eval_string("{flightIndex}"));
		  	strcat(cancel_flights_body, "=on&");
		}
		
		for (i=1; i<=flight_count_before_remove; i++)
		{
			strcat(cancel_flights_body, "flightID=");
			strcat(cancel_flights_body, lr_paramarr_idx("flightID", i));
		  	strcat(cancel_flights_body, "&");
		}
		
		strcat(cancel_flights_body, "removeFlights.x=56&removeFlights.y=12&");
		
		for (i=1; i<=flight_count_before_remove; i++)
		{
			lr_save_int(i,"flightIndex");
			strcat(cancel_flights_body, ".cgifields=");
			strcat(cancel_flights_body, lr_eval_string("{flightIndex}"));
			if(i!=flight_count_before_remove) {
				strcat(cancel_flights_body, "&");
			}
		}
		
		flight_count_to_be_left = flight_count_before_remove - random_flights_number_to_remove;
		
		lr_save_int(flight_count_to_be_left, "flightsCountToBeLeft");
		
		lr_param_sprintf("CancelFlightsBodyParam", "%s",cancel_flights_body);
		
		lr_output_message("CancelFlightsBodyParam =%s", cancel_flights_body);
		
		web_reg_save_param_ex(
			"ParamName=flightID_after_remove",
			"LB=flightID\" value=\"",
			"RB=\"  />",
			"NotFound=warning",
			"Ordinal=All",
		LAST);
		
		/*if(flight_count_to_be_left == 0) {
			web_reg_find("Text=No flights have been reserved.", LAST);
		} else {
			web_reg_find("Text=A total of {flightsCountToBeLeft} scheduled flights.", LAST);
		}*/
		
		web_custom_request("itinerary.pl_2",
			"URL={protocol}://{host}:{port}/cgi-bin/itinerary.pl", 
			"Method=POST", 
			"Resource=0", 
			"RecContentType=text/html", 
			"Referer={protocol}://{host}:{port}/cgi-bin/itinerary.pl", 
			"Snapshot=t3.inf", 
			"Mode=HTTP", 
			"Body={CancelFlightsBodyParam}", 
			LAST);
		
		flight_count_after_remove = atoi(lr_eval_string("{flightID_after_remove_count}"));
		removed_flights_count = flight_count_before_remove - flight_count_after_remove;
		
		if(removed_flights_count != random_flights_number_to_remove) {
			lr_error_message("Number of flights selected to remove is %d but only %d removed", random_flights_number_to_remove, removed_flights_count);
		}
		
		for(i = 1; i <= random_flights_number_to_remove; i++) {
			for(j = 1; j <= flight_count_after_remove; j++) {
				if(strcmp(lr_paramarr_idx("flightID", i), lr_paramarr_idx("flightID_after_remove", j)) == 0) {
					lr_error_message("Flight %s must be removed", lr_paramarr_idx("flightID_after_remove", i));
				}
			}
		}
		
		/*web_custom_request("itinerary.pl_2", 
			"URL={protocol}://{host}:{port}/cgi-bin/itinerary.pl", 
			"Method=POST", 
			"Resource=0", 
			"RecContentType=text/html", 
			"Referer={protocol}://{host}:{port}/cgi-bin/itinerary.pl", 
			"Snapshot=t9.inf", 
			"Mode=HTTP", 
			"Body=flightID=205745311-800-JB&flightID=205741166-1576-JB&flightID=205741166-2346-JB&3=on&1=on&flightID=205741166-2346-JB&removeFlights.x=56&removeFlights.y=12&.cgifields=4&.cgifields=1&.cgifields=3&.cgifields=2", 
			LAST);*/
		
		/*web_submit_data("itinerary.pl", 
			"Action={protocol}://{host}:{port}/cgi-bin/itinerary.pl", 
			"Method=POST", 
			"TargetFrame=", 
			"RecContentType=text/html", 
			"Referer={protocol}://{host}:{port}/cgi-bin/itinerary.pl", 
			"Snapshot=t4.inf", 
			"Mode=HTML", 
			ITEMDATA,
			"Name=flightID", "Value=205745311-800-JB", ENDITEM, 
			"Name=flightID", "Value=205745311-1569-JB", ENDITEM, 
			"Name=flightID", "Value=205741166-2346-JB", ENDITEM,
			"Name=1", "Value=on", ENDITEM,		
			"Name=flightID", "Value=205741166-3115-JB", ENDITEM, 
			"Name=flightID", "Value=205741166-3884-JB", ENDITEM,
			"Name=flightID", "Value=205741166-4653-JB", ENDITEM,
			"Name=removeFlights.x", "Value=62", ENDITEM, 
			"Name=removeFlights.y", "Value=8", ENDITEM, 
			"Name=.cgifields", "Value=1", ENDITEM, 
			"Name=.cgifields", "Value=2", ENDITEM, 
			"Name=.cgifields", "Value=3", ENDITEM,  
			"Name=.cgifields", "Value=4", ENDITEM, 
			"Name=.cgifields", "Value=5", ENDITEM, 
			"Name=.cgifields", "Value=6", ENDITEM,
			LAST);*/
	
		lr_end_transaction("remove_ticket",LR_AUTO);
		
		lr_think_time(5);
	}

	sign_off();

	lr_end_transaction("UC2_RemoveTicket",LR_AUTO);

	return 0;
}