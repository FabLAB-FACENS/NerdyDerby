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
    public Dropdown PistaCOMPortsDropDown;//Arduino Pista
    public Dropdown RegistroCOMPortsDropDown;//Arduino Regristro
    public Dropdown webcamDropDown;
    SerialPort arduinoPista;
    SerialPort arduinoRegistro;
    public Sprite OKSprite;
    public Sprite NotOKSprite;
    public Image arduinoPistaStatusImage;
    public Image arduinoRegistroStatusImage;
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
        COMPorts.Add(PlayerPrefs.GetString("ArduinoCOMRegistro"));
        COMPorts.Add(PlayerPrefs.GetString("ArduinoCOMPista"));
        foreach (string item in aux)
        {
            if(!COMPorts.Contains(item))
            {
                COMPorts.Add(item);
            }
            
        }
        PistaCOMPortsDropDown.ClearOptions();
        PistaCOMPortsDropDown.AddOptions(COMPorts);
        RegistroCOMPortsDropDown.ClearOptions();
        RegistroCOMPortsDropDown.AddOptions(COMPorts);
        PistaArduinoCOM_Change();
        RegistroArduinoCOM_Change();
    }

    public void PistaArduinoCOM_Change()
    {
        StartCoroutine("PistaArduinoCOMTest");
    }
    public void RegistroArduinoCOM_Change()
    {
        StartCoroutine("RegistroArduinoCOMTest");
    }

    IEnumerator PistaArduinoCOMTest()
    {
        arduinoPistaStatusImage.sprite = null;
        arduinoPistaStatusImage.color = Color.clear;
        bool isConnected = false;
        try
        {
            arduinoPista = new SerialPort(PistaCOMPortsDropDown.options[PistaCOMPortsDropDown.value].text, 9600);
            arduinoPista.ReadTimeout = 50;
            arduinoPista.Open();
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
                arduinoPista.Write("TEST");
                try
                {
                    message = arduinoPista.ReadLine();
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
                arduinoPistaStatusImage.sprite = OKSprite;
                arduinoPistaStatusImage.color = Color.green;
                PlayerPrefs.SetString("ArduinoCOMPista", PistaCOMPortsDropDown.options[PistaCOMPortsDropDown.value].text);
            }
            else
            {
                Debug.Log("Not Connected");
                arduinoPistaStatusImage.sprite = NotOKSprite;
                arduinoPistaStatusImage.color = Color.red;
            }
        }
        else
        {
            Debug.Log("Not Connected");
            arduinoPistaStatusImage.sprite = NotOKSprite;
            arduinoPistaStatusImage.color = Color.red;
        }
        arduinoPista.Close();
    }

    IEnumerator RegistroArduinoCOMTest()
    {
        arduinoRegistroStatusImage.sprite = null;
        arduinoRegistroStatusImage.color = Color.clear;
        bool isConnected = false;
        try
        {
            arduinoRegistro = new SerialPort(RegistroCOMPortsDropDown.options[RegistroCOMPortsDropDown.value].text, 9600);
            arduinoRegistro.ReadTimeout = 50;
            arduinoRegistro.Open();
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
                arduinoRegistro.Write("TEST");
                try
                {
                    message = arduinoRegistro.ReadLine();
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
                arduinoRegistroStatusImage.sprite = OKSprite;
                arduinoRegistroStatusImage.color = Color.green;
                PlayerPrefs.SetString("ArduinoCOMRegistro", RegistroCOMPortsDropDown.options[RegistroCOMPortsDropDown.value].text);
            }
            else
            {
                Debug.Log("Not Connected");
                arduinoRegistroStatusImage.sprite = NotOKSprite;
                arduinoRegistroStatusImage.color = Color.red;
            }
        }
        else
        {
            Debug.Log("Not Connected");
            arduinoRegistroStatusImage.sprite = NotOKSprite;
            arduinoRegistroStatusImage.color = Color.red;
        }
        arduinoRegistro.Close();
    }
}
