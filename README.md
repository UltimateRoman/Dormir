# Dormir
<br/>

![mainpic](Poster.png?raw=true)

<br/>




<b><i>A project which aims to help people fix their broken sleep schedules</i></b>

## Inspiration

Sleep is critical to our physical health and the effective functioning of our immune system. It is also a key promoter of emotional wellness and mental health, helping to beat back stress, depression, and anxiety. Millions of people suffered from insomnia even before the coronavirus and unfortunately, the pandemic creates a host of new challenges — even for people who previously had no sleeping problems. Recent studies have found that that nearly everyone’s sleep was affected by the pandemic in some way: one in six lost sleep, one in five slept the same amount but shifted their bedtime later, and one in four actually gained sleep but ended up with a later biological clock. Some of the major causes which have aggravated it include disruption of daily life, anxiety and worry, depression and isolation, binge-watching and excessive screen time.  

This is also an issue which resonates especially with but not limited to our APAC hacker friends, who usually stay up at odd times in their time-zones to attend live-streams or other events. Such habits on a prolonged basis can be detrimental to their sleep schedule as well as their mental health in the long run.
So it is extremely necessary for people to cultivate a healthy sleep schedule considering the huge amount of significance pertaining to the same.  Fixing sleep problems can also end up helping with mental health and even though stress can be hard to manage, sleep is something that could be potentially fixable. 

Hence we decided to build a hack to help people get better sleep and fix their messed up sleep schedules, which could also consequently solve a lot of other problems as well.

## What it does

Dormir is essentially a project which incorporates a set of proven sleep improvement techniques and enforces it upon the user in a fun and interactive way. It consists of a Web-app and an IOT based hardware module.

The IOT device has a set of sensors which detects the user’s bedroom conditions such as the light intensity, noise and temperature. It then conveys to the user any necessary but simple sleep-friendly reforms based on this data. For example, if the room temperature is above the optimal value, it advises them to consider taking a bath. 

It can function as a sleep monitor and logs the time when the user hits the bed and their waking time on to the database on a daily basis. It can also function as an alarm, which rings daily based on the wake-up time chosen by the user on the web-app during registration. This totally eliminates any excuses that the user would have for taking mobiles/screens to their bed, which could have seriously impacted their sleep and kept them awake for longer. It also presents with some morning tips such as getting some sunlight or performing a random exercise, all of which are instrumental to the cause.

The web-app helps user view their sleeping pattern trends over the days, based on the data recorded by the device. This will help them analyze what had gone wrong on particular days and take action to not repeat the same.

## How we built it

The web-app was built using HTML, CSS, Bootstrap for the front-end, and Flask and SQLite for the back-end.

 The IoT device consists of an Arduino Uno, sensors including a light intensity sensor, DHT, etc, a buzzer, a push-button, and an OLED display. It is interfaced with a Bolt micro-controller containing an ESP8266 WiFi module using serial communication. The Bolt device is in turn connected to the Bolt Cloud and can be managed using the boltiot python package.

## Challenges we ran into

1. Virtual Collaboration. Some of our team-members got occupied with urgent personal matters in between but we were able to get back together.

2. Establishing communication between the micro-controllers. We had to spend a significant amount of time and effort to optimize it according to the project requirements.

3. Lack of time. Though our idea was quite an ambitious one, the time constraint inhibited us from showcasing it in full glory. The web-app is functional but could only be done minimally.

## Accomplishments that we're proud of

1. We're glad that could try out and learn something new this weekend and had great fun collaborating.

2. We take pride in having been able to build a completely functional project within the hackathon duration.

3. We are also super proud that we did our best in trying to solve a very significant issue that has widely affected people around the globe.

## What we learned

1. Using Flask along with SQLite.

2. Bolt python library.

3. Using UART to interface two different micro-controllers.

## What's next for Dormir

1. Use more advanced sensors to better detect sleep patterns.

2. Improving web-app functionalities and introducing a reward system for users maintaining steady progress.

3. Designing a more compact hardware module.

3. Better UI/UX to help facilitate adoption among the masses.



## Setup Dormir

### Hardware setup

- Connnect the components according to the circuit shown below at a convenient location and connect to power.

 <br />
 
![circuit](Hardware/Module.jpg?raw=true)

<br/>

- Upload the [sketch](Hardware/sketch/sketch.ino) onto your Arduino Uno.


### Clone the repo

```
$ git clone https://github.com/UltimateRoman/Dormir
$ cd Dormir
```

### Install dependencies

```
$ cd Flask_App
$ pip install -r requirements.txt
```
### Run the Web-App

```
$ python app.py
```

- Visit locahost:5000 in your web browser and enjoy the Dormir experience.
