void home_page() {
	lr_start_transaction("home_page");
	
	web_add_auto_header("Sec-Fetch-Dest", 
		"frame");

	web_add_auto_header("Sec-Fetch-Mode", 
		"navigate");

	web_add_auto_header("Sec-Fetch-Site", 
		"same-origin");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	web_add_auto_header("sec-ch-ua", 
		"\"Google Chrome\";v=\"105\", \"Not)A;Brand\";v=\"8\", \"Chromium\";v=\"105\"");

	web_add_auto_header("sec-ch-ua-mobile", 
		"?0");

	web_add_auto_header("sec-ch-ua-platform", 
		"\"Windows\"");

	web_reg_save_param_ex(
		"ParamName=userSession",
		"LB=name=\"userSession\" value=\"",
		"RB=\"/>",
		SEARCH_FILTERS,
		LAST);

	web_reg_find("Text=A Session ID has been created and loaded into a cookie called MSO", LAST);

	web_url("welcome.pl", 
		"URL={protocol}://{host}:{port}/cgi-bin/welcome.pl?signOff=true", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer={protocol}://{host}:{port}/WebTours/", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);
		
	lr_end_transaction("home_page",LR_AUTO);
}

void login() {
	lr_start_transaction("login");
	
	web_add_header("Origin", 
		"{protocol}://{host}:{port}");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");
	
	web_reg_find("Text=User password was correct", LAST);

	web_reg_find("Search=Headers",
		"Text=firstName&{firstName}",
		LAST);
	
	web_reg_find("Search=Headers",
		"Text=lastName&{lastName}",
		LAST);
	
	web_submit_data("login.pl",
		"Action={protocol}://{host}:{port}/cgi-bin/login.pl",
		"Method=POST",
		"TargetFrame=body",
		"RecContentType=text/html",
		"Referer={protocol}://{host}:{port}/cgi-bin/nav.pl?in=home",
		"Snapshot=t2.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=userSession", "Value={userSession}", ENDITEM,
		"Name=username", "Value={username}", ENDITEM,
		"Name=password", "Value={password}", ENDITEM,
		"Name=login.x", "Value=0", ENDITEM,
		"Name=login.y", "Value=0", ENDITEM,
		"Name=JSFormSubmit", "Value=off", ENDITEM,
		LAST);
		
	lr_end_transaction("login",LR_AUTO);
}

void flights_page() {
	lr_start_transaction("flights_page");
	
	web_revert_auto_header("Sec-Fetch-User");
	
	web_reg_find("Text=User has returned to the search page", LAST);

	web_url("Search Flights Button", 
		"URL={protocol}://{host}:{port}/cgi-bin/welcome.pl?page=search", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer={protocol}://{host}:{port}/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("flights_page",LR_AUTO);
}

void choose_ticket() {
	lr_start_transaction("choose_ticket");
	
	web_reg_find("Text=firstName\" value=\"{firstName}", LAST);
	web_reg_find("Text=lastName\" value=\"{lastName}", LAST);
	web_reg_find("Text=value=\"{firstName} {lastName}", LAST);
	
	web_submit_data("reservations.pl_2", 
		"Action={protocol}://{host}:{port}/cgi-bin/reservations.pl", 
		"TargetFrame=", 
		"Method=POST", 
		"RecContentType=text/html", 
		"Referer={protocol}://{host}:{port}/cgi-bin/reservations.pl", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=outboundFlight", "Value={ticket}", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=seatType", "Value={seatType}", ENDITEM, 
		"Name=seatPref", "Value={seatPref}", ENDITEM, 
		"Name=reserveFlights.x", "Value=54", ENDITEM, 
		"Name=reserveFlights.y", "Value=5", ENDITEM, 
		LAST);
		
	lr_end_transaction("choose_ticket",LR_AUTO);
}

void search_flight() {
	
	char* ticket;
	char ticketArr[20];
	char* flightNumber;
	int flightPrice;
	int return_value;
	char* departureCity;
	char* arrivalCity;
	int numPassengers;
	
	lr_start_transaction("search_flight");
	
	numPassengers = atoi(lr_eval_string("{numPassengers}"));
	departureCity = lr_eval_string("{cityToChoose}");
	lr_save_string(departureCity, "departureCity");
	arrivalCity = lr_eval_string("{cityToChoose}");
	lr_save_string(arrivalCity, "arrivalCity");
	
	web_add_auto_header("Origin", 
		"{protocol}://{host}:{port}");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	web_reg_find("Text=Flight departing from <B>{departureCity}</B> to <B>{arrivalCity}</B> on <B>{departDate}</B>", LAST);
	
	web_reg_save_param_ex(
		"ParamName=outboundFlight",
		"LB=outboundFlight\" value=\"",
		"RB=\"",
		"NotFound=error",
		"Ordinal=All",
		SEARCH_FILTERS,
		LAST);

	web_submit_data("reservations.pl", 
		"Action={protocol}://{host}:{port}/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer={protocol}://{host}:{port}/cgi-bin/reservations.pl?page=welcome", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=depart", "Value={departureCity}", ENDITEM, 
		"Name=departDate", "Value={departDate}", ENDITEM, 
		"Name=arrive", "Value={arrivalCity}", ENDITEM, 
		"Name=returnDate", "Value={returnDate}", ENDITEM, 
		"Name=numPassengers", "Value=3", ENDITEM, 
		"Name=seatPref", "Value={seatPref}", ENDITEM, 
		"Name=seatType", "Value={seatType}", ENDITEM, 
		"Name=findFlights.x", "Value=49", ENDITEM, 
		"Name=findFlights.y", "Value=11", ENDITEM, 
		"Name=.cgifields", "Value=roundtrip", ENDITEM, 
		"Name=.cgifields", "Value=seatType", ENDITEM, 
		"Name=.cgifields", "Value=seatPref", ENDITEM, 
		LAST);

	ticket = lr_paramarr_random("outboundFlight");
	
	strcpy(ticketArr,ticket);
	
	flightNumber = (char*)strtok(ticketArr,";");
	flightPrice = atoi(strtok(NULL,";"));
	
	flightPrice = flightPrice * numPassengers;
	
	lr_save_string(ticket, "ticket");
	lr_save_string(flightNumber, "flightNumber");
	lr_save_int(flightPrice, "flightPrice");
	
	lr_end_transaction("search_flight",LR_AUTO);
}

void payment_details() {
	int numPassengers;
	
	lr_start_transaction("payment_details");
	
	numPassengers = atoi(lr_eval_string("{numPassengers}"));
	
	web_reg_find("Text=Flight {flightNumber} leaves {departureCity}  for {arrivalCity}", LAST);
	web_reg_find("Text=<b>{firstName}{lastName}'s Flight Invoice", LAST);
	web_reg_find("Text=${flightPrice}", LAST);
	
	if(numPassengers == 1) {
		web_submit_data("reservations.pl_3", 
		"Action={protocol}://{host}:{port}/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer={protocol}://{host}:{port}/cgi-bin/reservations.pl", 
		"Snapshot=t6.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=firstName", "Value={firstName}", ENDITEM, 
		"Name=lastName", "Value={lastName}", ENDITEM, 
		"Name=address1", "Value={street}", ENDITEM, 
		"Name=address2", "Value={city}", ENDITEM, 
		"Name=pass1", "Value={firstName} {lastName}", ENDITEM,
		"Name=creditCard", "Value={creditCard}", ENDITEM, 
		"Name=expDate", "Value={expDate}", ENDITEM, 
		"Name=oldCCOption", "Value=", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=seatType", "Value={seatType}", ENDITEM, 
		"Name=seatPref", "Value={seatPref}", ENDITEM, 
		"Name=outboundFlight", "Value={ticket}", ENDITEM, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=returnFlight", "Value=", ENDITEM, 
		"Name=JSFormSubmit", "Value=off", ENDITEM, 
		"Name=buyFlights.x", "Value=20", ENDITEM, 
		"Name=buyFlights.y", "Value=7", ENDITEM, 
		"Name=.cgifields", "Value=saveCC", ENDITEM, 
		LAST);
	} else if(numPassengers == 2) {
		web_submit_data("reservations.pl_3", 
		"Action={protocol}://{host}:{port}/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer={protocol}://{host}:{port}/cgi-bin/reservations.pl", 
		"Snapshot=t6.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=firstName", "Value={firstName}", ENDITEM, 
		"Name=lastName", "Value={lastName}", ENDITEM, 
		"Name=address1", "Value={street}", ENDITEM, 
		"Name=address2", "Value={city}", ENDITEM, 
		"Name=pass1", "Value={firstName} {lastName}", ENDITEM, 
		"Name=pass2", "Value={randName} {randSurname}", ENDITEM, 
		"Name=creditCard", "Value={creditCard}", ENDITEM, 
		"Name=expDate", "Value={expDate}", ENDITEM, 
		"Name=oldCCOption", "Value=", ENDITEM, 
		"Name=numPassengers", "Value=2", ENDITEM, 
		"Name=seatType", "Value={seatType}", ENDITEM, 
		"Name=seatPref", "Value={seatPref}", ENDITEM, 
		"Name=outboundFlight", "Value={ticket}", ENDITEM, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=returnFlight", "Value=", ENDITEM, 
		"Name=JSFormSubmit", "Value=off", ENDITEM, 
		"Name=buyFlights.x", "Value=20", ENDITEM, 
		"Name=buyFlights.y", "Value=7", ENDITEM, 
		"Name=.cgifields", "Value=saveCC", ENDITEM, 
		LAST);
	} else if (numPassengers == 3) {
		web_submit_data("reservations.pl_3", 
		"Action={protocol}://{host}:{port}/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer={protocol}://{host}:{port}/cgi-bin/reservations.pl", 
		"Snapshot=t6.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=firstName", "Value={firstName}", ENDITEM, 
		"Name=lastName", "Value={lastName}", ENDITEM, 
		"Name=address1", "Value={street}", ENDITEM, 
		"Name=address2", "Value={city}", ENDITEM, 
		"Name=pass1", "Value={firstName} {lastName}", ENDITEM, 
		"Name=pass2", "Value={randName} {randSurname}", ENDITEM, 
		"Name=pass3", "Value={randName} {randSurname}", ENDITEM, 
		"Name=creditCard", "Value={creditCard}", ENDITEM, 
		"Name=expDate", "Value={expDate}", ENDITEM, 
		"Name=oldCCOption", "Value=", ENDITEM, 
		"Name=numPassengers", "Value=3", ENDITEM, 
		"Name=seatType", "Value={seatType}", ENDITEM, 
		"Name=seatPref", "Value={seatPref}", ENDITEM, 
		"Name=outboundFlight", "Value={ticket}", ENDITEM, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=returnFlight", "Value=", ENDITEM, 
		"Name=JSFormSubmit", "Value=off", ENDITEM, 
		"Name=buyFlights.x", "Value=20", ENDITEM, 
		"Name=buyFlights.y", "Value=7", ENDITEM, 
		"Name=.cgifields", "Value=saveCC", ENDITEM, 
		LAST);
	}
	
	lr_end_transaction("payment_details",LR_AUTO);
}

void itinerary() {
	lr_start_transaction("itinerary");
	
	web_revert_auto_header("Sec-Fetch-User");
	
	web_reg_find("Text=User wants the intineraries", LAST);

	web_url("Itinerary Button", 
		"URL={protocol}://{host}:{port}/cgi-bin/welcome.pl?page=itinerary", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer={protocol}://{host}:{port}/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);
		
	lr_end_transaction("itinerary",LR_AUTO);
}

void sign_off() {
	lr_start_transaction("sign_off");
	
	web_revert_auto_header("Sec-Fetch-User");

	web_reg_find("Text=Welcome to the Web Tours site.", LAST);
	
	web_url("SignOff Button", 
		"URL={protocol}://{host}:{port}/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer={protocol}://{host}:{port}/cgi-bin/nav.pl?page=menu&in=itinerary", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		LAST);
		
	lr_end_transaction("sign_off",LR_AUTO);
}