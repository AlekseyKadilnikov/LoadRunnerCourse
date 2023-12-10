Action()
{
	int i;
	long file;
	char *filename=".\\users.dat";
	int USERNAME_SIZE;
	int PASSWORD_SIZE;
	char rand_username[15];
	char rand_password[15];
	
	srand(time(NULL));
	
	USERNAME_SIZE=3+rand()%(10-3+1);
	PASSWORD_SIZE=3+rand()%(10-3+1);
	
	for(i = 0; i < USERNAME_SIZE; i++) {
		strcat(rand_username, lr_eval_string("{RandCharLowercase}"));
	}
	
	for(i = 0; i < PASSWORD_SIZE; i++) {
		strcat(rand_password, lr_eval_string("{RandCharLowercase}"));
	}
	
	lr_param_sprintf("Username", rand_username);
	lr_param_sprintf("Password", rand_password);
		
	lr_start_transaction("UC3_Registration");

	lr_start_transaction("home_page");

	home_page();

	lr_end_transaction("home_page",LR_AUTO);
	
	lr_think_time(12);

	lr_start_transaction("sign_up_page");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	web_reg_find("Text=<title>User Information</title>", LAST);
	
	web_url("login.pl", 
		"URL={protocol}://{host}:{port}/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer={protocol}://{host}:{port}/WebTours/home.html", 
		"Snapshot=t2.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("sign_up_page",LR_AUTO);
	
	lr_think_time(12);

	lr_start_transaction("sign_up");

	web_add_header("Origin", 
		"{protocol}://{host}:{port}");

	
	web_reg_find("Text=<title>Welcome to Web Tours</title>", LAST);
	
	web_reg_find("Search=Headers",
		"Text=firstName&{randName}",
		LAST);
	
	web_reg_find("Search=Headers",
		"Text=lastName&{randSurname}",
		LAST);
	
	web_submit_data("login.pl_2", 
		"Action={protocol}://{host}:{port}/cgi-bin/login.pl", 
		"Method=POST", 
		"TargetFrame=info", 
		"RecContentType=text/html", 
		"Referer={protocol}://{host}:{port}/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=username", "Value={Username}", ENDITEM, 
		"Name=password", "Value={Password}", ENDITEM, 
		"Name=passwordConfirm", "Value={Password}", ENDITEM, 
		"Name=firstName", "Value={randName}", ENDITEM, 
		"Name=lastName", "Value={randSurname}", ENDITEM, 
		"Name=address1", "Value={RandStreet}", ENDITEM, 
		"Name=address2", "Value={RandCity}", ENDITEM, 
		"Name=register.x", "Value=25", ENDITEM, 
		"Name=register.y", "Value=8", ENDITEM, 
		LAST);

	lr_end_transaction("sign_up",LR_AUTO);
	
	lr_think_time(12);

	lr_start_transaction("home_page");

	web_revert_auto_header("Sec-Fetch-User");

	web_add_header("Sec-Fetch-User", 
		"?1");

	web_reg_find("Text=User has returned to the home page", LAST);
	
	web_url("button_next.gif", 
		"URL={protocol}://{host}:{port}/cgi-bin/welcome.pl?page=menus", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer={protocol}://{host}:{port}/cgi-bin/login.pl", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("home_page",LR_AUTO);
		
	if((file=fopen(filename,"a"))==NULL) {
		lr_error_message("Cannot open %s", filename);
		
		return -1;
	}
	
	fprintf(file, 
	        "%s,%s,%s,%s,%s,%s\n",
	        lr_eval_string("{Username}"),
	        lr_eval_string("{Password}"),
	       	lr_eval_string("{randName}"),
	      	lr_eval_string("{randSurname}"),
	     	lr_eval_string("{RandStreet}"),
	    	lr_eval_string("{RandCity}")
	);
	
	fclose(file);
	
	strcpy(rand_username, "");
	strcpy(rand_password, "");
	
	lr_end_transaction("UC3_Registration",LR_AUTO);

	return 0;
}