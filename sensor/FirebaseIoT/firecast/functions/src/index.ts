import * as functions from "firebase-functions";

export const helloWorld = functions.https.onRequest((request, response) => {
    console.log("Hello")
   response.send("Hello from Firebase!");
 });
