HTTPParser
-------------------------------------------------------------
HTTPParser is an apache access log parser coded in Python. It analyzes the log file provided as command line argument. The analyzed data is classified into global and website specific data. The accepted log file should have the following format:

%h %l %u %t \"%r\" %>s %b \"%{Referer}i\" \"%{User-agent}i\" (Ref: http://httpd.apache.org/docs/2.2/logs.html)

We have used regular expressions to dissect different fields of the log entries. A new object is created for each website found in the log and all information specific to that website is stored in that object. A global dictionary is maintained which maps the name of website (key) to the reference of its corresponding object (value).

Global data consists of traffic sources and user agents data sorted according to their frequency of occurence throughout the log. The data stored in website object consists of-
1. The page URLs associated with number of hits on that page
2. The number of each type of HTTP Response codes generated
3. Daywise hits on the website
4. HTTP Referers in the request along with their frequency.

The program presents a menu to the user displaying the websites that have been found in the log file provided. A website can be selected to display its top pages, datewise traffic, top referers and request status data. Displaying data in raw counts and frequencies doesn't help the user get the relative perspective. Hence, ALL DATA IS PRESENTED IN PERCENTAGES. This program works for all access log files which adhere to the above mentioned format.

Additionally, we have used Apache logs viewer tool (http://www.apacheviewer.com/) to generate relavant graphs and charts. It is found that the numerical figures generated from this tool match with that of our program. Hence, the correct execution of program is verified.

--------------------------------------------------------------
OUTPUT OF THE PROGRAM FOR weblog.txt
--------------------------------------------------------------

C:\Users\user\Desktop>python HTTPParser.py weblog.txt

Top traffic sources:

66.249.70.102                  : 25.23%
74.6.22.103                    : 11.84%
194.8.74.220                   : 3.82%
216.239.45.4                   : 3.78%
194.8.75.163                   : 3.31%
70.231.229.80                  : 2.88%
194.8.75.149                   : 2.81%
72.30.142.90                   : 2.59%
76.89.159.20                   : 2.45%
24.6.98.146                    : 2.41%


Top browsers:

Googlebot                      : 25.03%
MSIE                           : 21.82%
Firefox                        : 17.79%
Yahoo                          : 15.24%
Safari                         : 10.48%

------------------------------------------------------------

Websites found:

1. recipewithme
2. kinneryandrajan
3. twibuzz
0. Exit

Select one to get more details:
2
------------------------------------------------------------

KINNERYANDRAJAN Stats :

------------------------------------------------------------
TOP PAGES:-

/?page_id=2                                        : 17.43%
/wp-comments-post.php                              : 16.25%
/                                                  : 5.77%
/wp-content/plugins/wp-recaptcha/recaptcha.css     : 4.12%
/wp-content/themes/inove/style.css                 : 3.77%


DATEWISE TRAFFIC:-

14/May/2009                                        : 15.31%
17/May/2009                                        : 14.96%
18/May/2009                                        : 8.83%
16/May/2009                                        : 11.66%
15/May/2009                                        : 24.73%
19/May/2009                                        : 24.5%


TOP REFERERS:-

http://www.kinneryandrajan.com/?page_id=2          : 47.09%
http://www.kinneryandrajan.com/                    : 26.01%
http://www.kinneryandrajan.com/?p=1                : 4.33%
http://www.kinneryandrajan.com/?cat=1              : 3.74%
http://www.kinneryandrajan.com/wp-content/themes/i : 3.29%


REQUEST STATUS:-

Successful requests                                : 65.25%
Failed requests                                    : 34.75%

------------------------------------------------------------

Websites found:

1. recipewithme
2. kinneryandrajan
3. twibuzz
0. Exit

Select one to get more details:
3
------------------------------------------------------------

TWIBUZZ Stats :

------------------------------------------------------------
TOP PAGES:-

/style.css                                         : 9.1%
/favicon.ico                                       : 6.85%
/                                                  : 6.64%
/logo.png                                          : 5.75%
/robots.txt                                        : 2.04%


DATEWISE TRAFFIC:-

14/May/2009                                        : 19.93%
17/May/2009                                        : 16.0%
18/May/2009                                        : 11.45%
16/May/2009                                        : 20.87%
15/May/2009                                        : 12.45%
19/May/2009                                        : 19.3%


TOP REFERERS:-

http://www.twibuzz.com/                            : 20.66%
http://twibuzz.com/                                : 7.5%
http://www.twibuzz.com/cgi/search.py               : 5.54%
http://www.twibuzz.com/cgi/search.py?query=google  : 4.18%
http://es.wikipedia.org/wiki/Twitter               : 2.95%


REQUEST STATUS:-

Successful requests                                : 85.46%
Failed requests                                    : 14.54%

------------------------------------------------------------

Websites found:

1. recipewithme
2. kinneryandrajan
3. twibuzz
0. Exit

Select one to get more details:
1
------------------------------------------------------------

RECIPEWITHME Stats :

------------------------------------------------------------
TOP PAGES:-

/robots.txt                                        : 41.18%
/                                                  : 29.41%
/favicon.ico                                       : 17.65%
/logo.png                                          : 5.88%
/recipes/recipes/view/cooking-mushu-chicken        : 5.88%


DATEWISE TRAFFIC:-

14/May/2009                                        : 11.76%
17/May/2009                                        : 11.76%
18/May/2009                                        : 11.76%
16/May/2009                                        : 5.88%
15/May/2009                                        : 23.53%
19/May/2009                                        : 35.29%


TOP REFERERS:-

http://www.recipewithme.com/recipes/recipes/view/c : 25.0%
http://www.roidsmall.com/links_catalog.php         : 25.0%
http://www.google.com/profiles/neurorajan          : 25.0%
http://www.recipewithme.com/                       : 25.0%


REQUEST STATUS:-

Successful requests                                : 52.94%
Failed requests                                    : 47.06%

------------------------------------------------------------

Websites found:

1. recipewithme
2. kinneryandrajan
3. twibuzz
0. Exit

Select one to get more details:
0

C:\Users\user\Desktop>