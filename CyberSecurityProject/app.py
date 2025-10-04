# First importing all the required libraries
import sqlite3

# Import flask and jinja stuff
from flask import Flask, render_template, request
from flask_session import Session


# Configure flask to application
app = Flask(__name__)

# Configure session to user filesystem ( instead of signed cookies )
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)
# Database now connected you can use queries like query = "Stuff" and then cursor.execute(query)




@app.after_request
def after_request(response):
    """Ensuring Respones Aret Cached"""
    response.headers["Cache-Control"] = "no-cache , no-store , must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response




# Main Route of my website

@app.route("/" , methods=["GET" , "POST"])
def index():

    # User clicked on the website and is redirected to main page
    if request.method == "GET":
        return render_template("index.html")
    
    # User clicked on one of buttons and must be submitted to correct routes
    elif request.method == "POST":

        # First storing what type of button was clicked
        button_clicked = request.form.get("button_value")

        # if Password checker was clicked
        if button_clicked == "password":
            return render_template("passwordChecker.html")
        
        # if Phishing was clicked
        elif button_clicked == "phishing":
            return render_template("phishingWebsite.html")
        
        # if Update Notifier was clicked
        elif button_clicked == "update":
            return render_template("updateNotifier.html")
        
        # if Credits was clicked
        elif  button_clicked == "credits":
            return render_template("credits.html")
        
    # Handling the special case if none gets clicked
        
    return render_template("index.html")
        



# Password Checker route code

@app.route("/passwordChecker" , methods= ["GET" , "POST"])
def password_checker():

    # If user clicked on the website using option
    if request.method == "GET":
        return render_template("passwordChecker.html")
    
    # If user submitted the password for verification
    elif request.method == "POST":

        # First getting the password from the form
        password_check = request.form.get("password_user")

        # Now making the logic
        password = str(password_check)

        # Initialize variables
        length_check = False
        upper_check = False
        lower_check = False
        decimal_check = False
        special_check = False

        # First we will be making sure that the password is greater than 8 characters
        if len(password) >= 6:
            length_check = True

        # Now we will be making the different checks needed
        for character in password:
            
            # Making sure that there is at least one upper case character
            if character.isupper():
                upper_check = True

            # Making sure that there is at least one lower case character
            elif character.islower():
                lower_check = True

            # Making sure that user put digits
            elif character.isdigit():
                decimal_check = True

            # Making sure that user put special characters
            elif character in ["$", "!", "%", "#", "@"]:
                special_check = True

        # Now returning the values to the form
        return render_template("passwordChecker.html", length_check=length_check, upper_check=upper_check, lower_check=lower_check, decimal_check=decimal_check, special_check=special_check)
    
    return render_template("passwordChecker.html")    




# Update Notifier Code
@app.route("/updateNotifier", methods=["GET", "POST"])
def updater():

    # If user clicked on the website to get into 
    if request.method == "GET":
        return render_template("updateNotifier.html")
    
    elif request.method == "POST":

          # First getting the button info from the user
          loginer = True

          # Now returning it to the form
          return render_template("updateNotifier.html" , loginer=loginer)
    
    return render_template("updateNotifier.html")



# Phishing website code

@app.route("/phishing", methods=["GET", "POST"])
def phisher():
    if request.method == "GET":
        return render_template("phishingWebsite.html")
    
    elif request.method == "POST":
        user_name = request.form.get("phishing_name")
        password_name = request.form.get("phishing_password")

        phisher_form_setter = True

        with sqlite3.connect("database.db") as connect:
            cursor = connect.cursor()

            cursor.execute("INSERT INTO inputData (username, password) VALUES (?, ?)", (user_name, password_name))
            connect.commit()

            # Fetch all rows of usernames and passwords
            cursor.execute("SELECT username, password FROM inputData")
            rows = cursor.fetchall()

        return render_template("phishingWebsite.html", rows=rows, phisher=phisher_form_setter)

    return render_template("phishingWebsite.html")

