using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System.IO;
using System;
using System.IO.Ports;

public class Settings : MonoBehaviour
{
    WebCamDevice[] webcams;
    List<String> COMPorts;
    List<String> webcamsList;
    public Dropdown COMPortsDropDown;
    public Dropdown webcamDropDown;
    SerialPort arduino;
    public Sprite OKSprite;
    public Sprite NotOKSprite;
    public Image arduinoStatusImage;
    public Image webcamStatusImage;
    public WebCamTexture backCam;
    // Start is called before the first frame update
    void Start()
    {

    }

    private void OnEnable()
    {
        LoadCOM();
        LoadWebCam();
    }

    // Update is called once per frame
    void Update()
    {

    }

    void LoadWebCam()
    {
        WebCamDevice[] devices = WebCamTexture.devices;
        webcamsList = new List<string>();
        webcamsList.Add(PlayerPrefs.GetString("webCamIndex"));
        
        foreach (WebCamDevice device in devices)
        {
            if(!webcamsList.Contains(device.name))
            {
                webcamsList.Add(device.name);
            }
            
        }

        webcamDropDown.ClearOptions();
        webcamDropDown.AddOptions(webcamsList);
        TestWebCam();
    }

    public void TestWebCam()
    {
        backCam = new WebCamTexture(webcamDropDown.options[webcamDropDown.value].text);
        backCam.Play();
        if (backCam.isPlaying)
        {
            PlayerPrefs.SetString("webCamIndex", webcamDropDown.options[webcamDropDown.value].text);
            Debug.Log($"Camera OK {webcamDropDown.options[webcamDropDown.value].text}");

            webcamStatusImage.sprite = OKSprite;
            webcamStatusImage.color = Color.green;
        }
        else
        {
            webcamStatusImage.sprite = NotOKSprite;
            webcamStatusImage.color = Color.red;
            Debug.Log("sem camera");
        }
        backCam.Stop();
    }

    void LoadCOM()
    {
        COMPorts = new List<string>();
        string[] aux = SerialPort.GetPortNames();
        COMPorts.Add(PlayerPrefs.GetString("ArduinoCOM"));
        foreach (string item in aux)
        {
            if(!COMPorts.Contains(item))
            {
                COMPorts.Add(item);
            }
            
        }
        COMPortsDropDown.ClearOptions();
        COMPortsDropDown.AddOptions(COMPorts);
        ArduinoCOM_Change();
    }

    public void ArduinoCOM_Change()
    {
        StartCoroutine("ArduinoCOMTest");
    }

    IEnumerator ArduinoCOMTest()
    {
        arduinoStatusImage.sprite = null;
        arduinoStatusImage.color = Color.clear;
        bool isConnected = false;
        try
        {
            arduino = new SerialPort(COMPortsDropDown.options[COMPortsDropDown.value].text, 9600);
            arduino.ReadTimeout = 50;
            arduino.Open();
            isConnected = true;
            Debug.Log("Connected to something");

        }
        catch (Exception ex)
        {
            Debug.Log(ex);

        }

        if (isConnected)
        {
            Debug.Log("Testing Arduino");
            //yield return new WaitForSeconds(1f);
            string message = "";
            for (int i = 0; i < 10; i++)
            {
                arduino.Write("TEST");
                try
                {
                    message = arduino.ReadLine();
                }
                catch (TimeoutException) { }

                if (message != "")
                {
                    Debug.Log(message);
                    break;
                }
                else
                {
                    Debug.Log("NADA");
                }
                yield return new WaitForSeconds(0.5f);
            }

            if (message.Contains("OK"))
            {
                Debug.Log("arduino OK");
                arduinoStatusImage.sprite = OKSprite;
                arduinoStatusImage.color = Color.green;
                PlayerPrefs.SetString("ArduinoCOM", COMPortsDropDown.options[COMPortsDropDown.value].text);
            }
            else
            {
                Debug.Log("Not Connected");
                arduinoStatusImage.sprite = NotOKSprite;
                arduinoStatusImage.color = Color.red;
            }
        }
        else
        {
            Debug.Log("Not Connected");
            arduinoStatusImage.sprite = NotOKSprite;
            arduinoStatusImage.color = Color.red;
        }
        arduino.Close();
    }
}
