#!usr/bin/python3

import re
import sys

class Website:
    '''Stores information collected from log for a particular website.'''

    def __init__(self, name):
        self.name = name                   #name of website e.g. twibuzz.com
        self.pages = {}                    # pages["page URL"] = no. of hits on that page 
        self.request_count = [0,0,0,0,0]   # classification according to HTTP response codes - 1xx, 2xx, 3xx, 4xx and 5xx
        self.daywise_count = {}            # daywise_count["date"] = no. of hits on that day
        self.referers = {}                 # referers["referer URL"] = no. of hits by that referer
        
try:
    file = open(sys.argv[1])
except IOError:
    print("Error opening file: " + sys.argv[1] + ". File does not exist.")
    print("Sample usage: prompt$python3 HTTPParser.py logfilename")
    

pattern = r'([\d\.]+) - - \[(.*?)\] "(\w+) (.*?) (HTTP/1.[01])" (\d+) (\d+|-) "(.*?)" "(.*?)"'

#For each record in the log file, the above RE separates following fields :-
#group 1 - IP Address
#group 2 - day and date
#group 3 - Request method (GET/POST)
#group 4 - Requested URL
#group 5 - HTTP Version
#group 6 - HTTP status (Response status)
#group 7 - Response size (in bytes)
#group 8 - Referer
#group 9 - User-agent

IPs = {}

websites = {}

user_agents = {"Firefox":0,"Safari":0,"MSIE":0,"Googlebot":0,"Yahoo":0,"Chrome":0,"Opera":0,"BrowseX":0,"Exabot":0}

for line in file:
    match = re.search(pattern,line)
    
    #####parsing IP address#####
    if match.group(1) not in IPs:
        IPs[match.group(1)] = 1
    else:
        IPs[match.group(1)] += 1

    #####parsing request line#####
    req_URL = re.search(r'^\w\w\w\.(.*?)\.\w\w\w(.*)',match.group(4))
    if req_URL == None:
        req_URL = re.search(r'^(.*?)\.\w\w\w(.*)',match.group(4))
    hostname = req_URL.group(1)
    page = req_URL.group(2)
    
    if hostname not in websites:
        website_obj = Website(hostname)
        websites[hostname] = website_obj
        websites[hostname].pages[page] = 1
    elif page not in websites[hostname].pages:
        websites[hostname].pages[page] = 1
    else:
        websites[hostname].pages[page] += 1

    #####parsing request type#####
    request_type = int(int(match.group(6))/100)
    websites[hostname].request_count[request_type - 1] += 1

    #####parsing date#####
    re_date = re.search(r'(.*?):',match.group(2))
    req_date = re_date.group(1)

    if req_date not in websites[hostname].daywise_count:
        websites[hostname].daywise_count[req_date] = 1
    else:
        websites[hostname].daywise_count[req_date] += 1

    #####parsing referer#####
    referer = match.group(8)
    if referer != "-":
        if referer not in websites[hostname].referers:
            websites[hostname].referers[referer] = 1
        else:
            websites[hostname].referers[referer] += 1

    #####parsing user agents#####
    for agent in user_agents:
        if agent in match.group(9):
            user_agents[agent] += 1
            

#####Display global data - IP addresses and user agents (browsers)
unique_IPs = sum(IPs.values())
print("\nTop traffic sources:\n")
[print(host.ljust(30) + " : " + str(round(IPs[host]*100/unique_IPs,2)) + "%") for host in sorted(IPs, key=IPs.get, reverse=True)[0:10]]


total_agents = sum(user_agents.values())
print("\n\nTop browsers:\n")
[print(agent.ljust(30) + " : " + str(round(user_agents[agent]*100/total_agents,2)) + "%") for agent in sorted(user_agents, key=user_agents.get, reverse=True)[0:5]]


while True:
    x = 1
    print("\n------------------------------------------------------------")
    print("\nWebsites found:\n")
    for i in list(websites.keys()):
        print(str(x) + ". " + i)
        x += 1
    print("0. Exit")
    print("\nSelect one to get more details: ")                         #Display websites list

    choice = int(input())                                               #Accept a choice
    if choice==0:
        quit(0)
    elif choice > len(websites.keys()):
        print("Invalid option selected.")
        continue
    choice -= 1

    site = list(websites.keys())[choice]
    
    total_visits = sum(websites[site].pages.values())                   #Generate its analyzed data
    total_referers = sum(websites[site].referers.values())
    top_pages = sorted(websites[site].pages, key=websites[site].pages.get, reverse=True)[0:5]
    top_referers = sorted(websites[site].referers, key=websites[site].referers.get, reverse=True)[0:5]

    print("------------------------------------------------------------")
    print("\n" + site.upper() + " Stats :\n")
    print("------------------------------------------------------------")
    print("TOP PAGES:-\n")                                              #Display the analysis
    for page in top_pages:
        print(page.ljust(50) + " : " + str(round(websites[site].pages[page]*100/total_visits,2)) + "%")

    print("\n\nDATEWISE TRAFFIC:-\n")
    for date in websites[site].daywise_count:
        print(date.ljust(50) + " : " + str(round(websites[site].daywise_count[date]*100/total_visits,2)) + "%")

    print("\n\nTOP REFERERS:-\n")
    for referer in top_referers:
        print(referer.ljust(50)[:50] +  " : " + str(round(websites[site].referers[referer]*100/total_referers,2)) + "%")

    print("\n\nREQUEST STATUS:-\n")
    status_codes = websites[site].request_count
    print("Successful requests".ljust(50) + " : " + str(round(status_codes[1]*100/total_visits,2)) + "%")
    print("Failed requests".ljust(50) + " : " + str(round((status_codes[2] + status_codes[3] + status_codes[4])*100/total_visits,2)) + "%\n\n")
