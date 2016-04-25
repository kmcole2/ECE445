// (c) 2013-2015 Don Coleman
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/* global mainPage, deviceList, refreshButton, statusDiv */
/* global detailPage, resultDiv, messageInput, sendButton, disconnectButton */
/* global cordova, bluetoothSerial  */
/* jshint browser: true , devel: true*/
'use strict';

    var flour_multiplier =  [1, 125,    28.35,  7.5,     3.13,   250,      500,       500,   2000];//Unit multiplier for
    var sugar_multiplier =  [1, 200,    28.35,  14,      4,      100,      200,       200,   800];   
    var milk_multiplier =   [1, 236.59, 29.5735,14.7868, 4.9289, 473.1765, 1000.0018, 946.353,3785.412];
    var water_multiplier =  [1, 236.59, 29.5735,14.7868, 4.9289, 473.1765, 1000.0018, 946.353,3785.412];     
    var units =["Grams", "Cups","Ounces","Tablespoons","Teaspoons","Pints","Quarts", "Liters", "Gallons"];
    


var app = {
    initialize: function() {
        this.bindEvents();
        this.showMainPage();
    },
    bindEvents: function() {

        var TOUCH_START = 'touchstart';
        if (window.navigator.msPointerEnabled) { // windows phone
            TOUCH_START = 'MSPointerDown';
        }
        document.addEventListener('deviceready', this.onDeviceReady, false);
        refreshButton.addEventListener(TOUCH_START, this.refreshDeviceList, false);
        sendButton.addEventListener(TOUCH_START, this.sendData, false);
        disconnectButton.addEventListener(TOUCH_START, this.disconnect, false);
        deviceList.addEventListener('touchstart', this.connect, false);
        printButton.addEventListener(TOUCH_START, this.printData, false);

    },
    onDeviceReady: function() {
        app.refreshDeviceList();
    },
    refreshDeviceList: function() {
        bluetoothSerial.list(app.onDeviceList, app.onError);
    },
    onDeviceList: function(devices) {
        var option;

        // remove existing devices
        deviceList.innerHTML = "";
        app.setStatus("");

        devices.forEach(function(device) {

            var listItem = document.createElement('li'),
                html = '<b>' + device.name + '</b><br/>' + device.id;

            listItem.innerHTML = html;

            if (cordova.platformId === 'windowsphone') {
              // This is a temporary hack until I get the list tap working
              var button = document.createElement('button');
              button.innerHTML = "Connect";
              button.addEventListener('click', app.connect, false);
              button.dataset = {};
              button.dataset.deviceId = device.id;
              listItem.appendChild(button);
            } else {
              listItem.dataset.deviceId = device.id;
            }
            deviceList.appendChild(listItem);
        });

        if (devices.length === 0) {

            option = document.createElement('option');
            option.innerHTML = "No Bluetooth Devices";
            deviceList.appendChild(option);

            if (cordova.platformId === "ios") { // BLE
                app.setStatus("No Bluetooth Peripherals Discovered.");
            } else { // Android or Windows Phone
                app.setStatus("Please Pair a Bluetooth Device.");
            }

        } else {
            app.setStatus("Found " + devices.length + " device" + (devices.length === 1 ? "." : "s."));
        }

    },
    connect: function(e) {
        var onConnect = function() {
                // subscribe for incoming data
                bluetoothSerial.subscribe('\n', app.onData, app.onError);

                resultDiv.innerHTML = "";
                app.setStatus("Connected");
                app.showDetailPage();
            };

        var deviceId = e.target.dataset.deviceId;
        if (!deviceId) { // try the parent
            deviceId = e.target.parentNode.dataset.deviceId;
        }

        bluetoothSerial.connect(deviceId, onConnect, app.onError);
    },
    onData: function(data) { // data received from Arduino
        console.log(data);
        resultDiv.innerHTML = resultDiv.innerHTML + "Received: " + data + "<br/>";
        resultDiv.scrollTop = resultDiv.scrollHeight;
    },
    sendData: function(event) { // send data to Arduino

        var success = function() {
            console.log("success");
            resultDiv.innerHTML = resultDiv.innerHTML + "Sent: " + messageInput.value + "<br/>";
            resultDiv.scrollTop = resultDiv.scrollHeight;
        };

        var failure = function() {
            alert("Failed writing data to Bluetooth peripheral");
        };

        var data = messageInput.value;
        bluetoothSerial.write(data, success, failure);
    },
    printData: function(event){
        var success = function(){

        }

        var failure = function(){

        }

        var form1,i;
        var q = [];    //quantities
        var pause = [];//pause
        var arrnum = 0;//starting with zero
        var select1,select2,select3,select4;
        var ctrlword;

        form1=document.getElementById("form1");

            q[0] = form1.elements["In1"].value; //Ingredient1 Quantity
            q[1] = form1.elements["In2"].value;
            q[2] = form1.elements["In3"].value;
            q[3] = form1.elements["In4"].value;

        //FORM VALIDATION 
        var numbers =  /^[-+]?[0-9]+\.[0-9]+$/; // /^[0-9]+$/;

        //if no input, output error to user
        if(!q[0] && !q[1] && !q[2] && !q[3]){
            document.getElementById("input1err").innerHTML = "Error: No values entered, form invalid";
        }
        //if input values aren't integers, output error to user 
        // else if((!q[0].match(numbers)) || (!q[1].match(numbers)) || (!q[2].match(numbers)) || (!q[3].match(numbers))){  
        //  // if(q1console.log("not int");
        //       console.log(Number.isInteger(1) + q[0] + parseInt(q[0]));
           //  document.getElementById("input1err").innerHTML ='Error: Please input positive quantity (ie. 1, 1.2, etc.)';  
           //  document.form1.In1.focus();  
           //  return false;  
        // }  
       //If quantity is specified, extract units of measure
        else {
                if(q[0]){
                    select1 = form1.units1;                     //Units of measure
                    q[0] = parseInt(q[0]*flour_multiplier[select1[select1.selectedIndex].value]);
                    arrnum++;
                    if(document.getElementById("pause1").checked){

                    }
                }
                if(q[1]){
                    select2 = form1.units2; 
                    q[1] = parseInt(q[1]*sugar_multiplier[select2[select2.selectedIndex].value]);
                    arrnum++;
                }       
                if(q[2]){
                    select3 = form1.units3; 
                    q[2] = parseInt(q[2]*milk_multiplier[select3[select3.selectedIndex].value]);
                    arrnum++;
                }
                if(q[3]){
                    select4 = form1.units4; 
                    q[3] = parseInt(q[3]*water_multiplier[select4[select4.selectedIndex].value]);
                    arrnum++;
                }
             var ctrlword = arrnum-1 + ",";

             for(i = 0; i < 4; i ++){
                if(q[i]){
                    var j = 1 + i;
                        if(document.getElementById("pause"+j).checked){
                            var p = "P";
                        } else {p  = "N";}
                        ctrlword += i + "," + q[i] + "," + p + ",";   
                    }
                }
                ctrlword += "*";
                console.log(units[select1[select1.selectedIndex].value]);
                console.log("control word = " + ctrlword);
                console.log("pause val = " + document.getElementById("pause1").checked);
                if(document.getElementById("pause1").checked){
                    console.log("pause registers");
                }
            document.getElementById("input1err").innerHTML = "control word = " + ctrlword;
        }
    },
    disconnect: function(event) {
        bluetoothSerial.disconnect(app.showMainPage, app.onError);
    },
    showMainPage: function() {
        mainPage.style.display = "";
        detailPage.style.display = "none";
    },
    showDetailPage: function() {
        mainPage.style.display = "none";
        detailPage.style.display = "";
    },
    setStatus: function(message) {
        console.log(message);

        window.clearTimeout(app.statusTimeout);
        statusDiv.innerHTML = message;
        statusDiv.className = 'fadein';

        // automatically clear the status with a timer
        app.statusTimeout = setTimeout(function () {
            statusDiv.className = 'fadeout';
        }, 5000);
    },
    onError: function(reason) {
        alert("ERROR: " + reason); // real apps should use notification.alert
    }
};
