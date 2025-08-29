# Rocket_Rover

# Understanding the Problem


Initially I searched Google and ChatGPT for info on it as I don't know what the ubx format and u-blox receiver are.

Then I put the small chunks of question into GPT to allow me understand what is going on here. So the first part of the code ublox_reader would receive the receiver's data which is 20 bytes (longitude,latitude ,time,date,whether gps has a valid position locked on) and then decodes it for the UBX packets as the data received is binary-encoded packets (structured sequence of bytes that can be read and interpreted by the required software based on our needs and here our need is the microcontroller inside the rover).


I was unable to form the code myself as I don't know the libraries used and I can't fully learn it in 1 hr so initially the first code made by GPT was fully understood by me which is ublox_reader.cpp and then afterwards I didn't have the time to understand the rest of the code so I left the understanding and tried to build as I believed that even GPT was building it I would be able to understand it myself a little bit and I did but later they said that we can fix the code till morning then i started making the code again using gpt and trying to fix the issue of the testcase's result not matching my result but i was unable to fix it as i dont know this things properly nor did i have time to understand them in detail.


 Afterwards i went through the entire code and tried to understand the entire code and made comments on each line of code too to show what it does in my own wording

While as required i was not able to build it but if i learn it properly in a bit more structured manner i believe i can understand and also form these types of codes  


# Thought Process and Implementation


This project is a GPS-based path planning system for a rover and it first decodes GPS data from u-blox GNSS module in UBX format which is converted to Converts GPS coordinates and then by checking the gridmap and understanding the location we can plan the fastest and most efficient path and finally generates odometry commands(movement of rover step by step like forward,rotate,reverse etc ) for rover movement


My first thought was to understand the topic and what is ubx and how it is converted and used here as if i dont understand the topic how can i even try to build something on it so i read the pdf given a little bit but it was headache to understand as i dont know what is going on there nor do i have the time to understand it properly so i opened the documentation online and searched on ChatGPT to understand it and then when i understood i first tried to frame the code myself but time was running out so i just put my edits along with the code given to gpt and it fixed it 

After learning i had more time till tomorrow noon I worked on the code and tried to understand the rest of the files also And I did understood a bit a bit the main problem is the math in the odometry and so dealing with it was a bit difficult

I also thought of trying out the dijkstra algorithm  But Chat GpT told the current one is better so I left it like that

Next i understood the odometry file and then i changed it up a bit and crossed checked it with gpt and then was done with it

After that i tried to understand how to run your testcases here and i did it and then i crosschecked the results and it didnt match and so i tried to fix the odometry multiples time but alas it didnt happen so i left it like this only 

Thanks to you i learnt a bit about advanced uses of c++