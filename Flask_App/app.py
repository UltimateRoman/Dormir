from flask import Flask, render_template, request, redirect
from cs50 import SQL

app = Flask(__name__)

app.config["TEMPLATES_AUTO_RELOAD"] = True

db = SQL("sqlite:///maindb.db")

@app.route("/", methods = ["GET" , "POST"])
def index():
    if request.method == "GET":
        return render_template("index.html")
    else:
        db.execute("INSERT INTO users(username, wtime) VALUES(:username, :wtime)", username=request.form.get("username"), wtime=request.form.get("time"))
        return redirect("/")

@app.route("/view")
def view():
    vdata = db.execute("SELECT * FROM records")
    return render_template("view.html", vdata=vdata)

if __name__ == '__main__':
    app.run()
