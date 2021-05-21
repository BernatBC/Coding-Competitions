using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Highscore_manager : MonoBehaviour
{
    public static Highscore_manager highscore_Manager;

    public Text Score1;
    public Text Score2;
    public Text Score3;
    public Text Score4;
    public Text Score5;

    private int[] Highscore = new int[5];

    private void Start()
    {

        if (highscore_Manager == null) {
            highscore_Manager = this;
            DontDestroyOnLoad(this);
        }
        else {
            Destroy(this);
        }
        
        if (PlayerPrefs.HasKey("score0")) Highscore[0] = PlayerPrefs.GetInt("score0");
        else Highscore[0] = 0;
        if (PlayerPrefs.HasKey("score1")) Highscore[1] = PlayerPrefs.GetInt("score1");
        else Highscore[0] = 0;
        if (PlayerPrefs.HasKey("score2")) Highscore[2] = PlayerPrefs.GetInt("score2");
        else Highscore[0] = 0;
        if (PlayerPrefs.HasKey("score3")) Highscore[3] = PlayerPrefs.GetInt("score3");
        else Highscore[0] = 0;
        if (PlayerPrefs.HasKey("score4")) Highscore[4] = PlayerPrefs.GetInt("score4");
        else Highscore[0] = 0;

        Update_chart();
    }

    private void Update()
    {
        if (Score1 == null && GameObject.Find("Highscore (1)").GetComponent<Text>() != null) Score1 = GameObject.Find("Highscore (1)").GetComponent<Text>();
        if (Score2 == null && GameObject.Find("Highscore (2)").GetComponent<Text>() != null) Score2 = GameObject.Find("Highscore (2)").GetComponent<Text>();
        if (Score3 == null && GameObject.Find("Highscore (3)").GetComponent<Text>() != null) Score3 = GameObject.Find("Highscore (3)").GetComponent<Text>();
        if (Score4 == null && GameObject.Find("Highscore (4)").GetComponent<Text>() != null) Score4 = GameObject.Find("Highscore (4)").GetComponent<Text>();
        if (Score5 == null && GameObject.Find("Highscore (5)").GetComponent<Text>() != null) Score5 = GameObject.Find("Highscore (5)").GetComponent<Text>();
        Update_chart();
    }

    public void Update_highscore(int new_score) {
        for (int i = 0; i < 5; ++i) {
            if (Highscore[i] < new_score) {
                int aux = Highscore[i];
                Highscore[i] = new_score;
                new_score = aux;
            }
        }
        Update_chart();
        //Save data
        PlayerPrefs.SetInt("score0", Highscore[0]);
        PlayerPrefs.SetInt("score1", Highscore[1]);
        PlayerPrefs.SetInt("score2", Highscore[2]);
        PlayerPrefs.SetInt("score3", Highscore[3]);
        PlayerPrefs.SetInt("score4", Highscore[4]);
    }

    private void Update_chart() {
        Score1.text = Highscore[0].ToString();
        Score2.text = Highscore[1].ToString();
        Score3.text = Highscore[2].ToString();
        Score4.text = Highscore[3].ToString();
        Score5.text = Highscore[4].ToString();
    }
}
