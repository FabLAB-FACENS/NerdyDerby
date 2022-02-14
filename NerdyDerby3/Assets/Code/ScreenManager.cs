using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ScreenManager : MonoBehaviour
{
    public GameObject MainMenu;
    public GameObject RankingPanel;
    public GameObject RegisterPanel;
    public GameObject RacePanel;
    public GameObject SettingsPanel;
    public GameObject resultsPanel;
    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Escape))
        {
            if (!resultsPanel.activeSelf)
            {
                ESC_Pressed();
            }
            
        }
        if (Input.GetKeyDown(KeyCode.F1))
        {
            
            F1_Press();
        }
    }
        
    public void OpenSetting()
    {
        SettingsPanel.SetActive(true);

    }
    public void  CloseSettings()
    {
        SettingsPanel.SetActive(false);
    }

    public void F1_Press()
    {
       
        RankingPanel.SetActive(false);
        MainMenu.SetActive(false);
    }

    public void RacePanel_Click()
    {
        RacePanel.SetActive(true);
        MainMenu.SetActive(false);
    }
    public void Ranking_Click()
    {
        RankingPanel.SetActive(true);
        MainMenu.SetActive(false);
    }
    public void Register_Click()
    {
        RegisterPanel.SetActive(true);
        MainMenu.SetActive(false);
    }
    public void ESC_Pressed()
    {
        RacePanel.SetActive(false);
        RegisterPanel.SetActive(false);
        RankingPanel.SetActive(false);
        MainMenu.SetActive(true);
    }
}
