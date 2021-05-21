using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class LevelManager : MonoBehaviour
{

     [SerializeField]
    private Text waveText;
    [SerializeField]
    private Text enemiesText;

     [SerializeField]
     private GameObject[] obstacles;

    [SerializeField]
    private GameObject[] enemies;

    private Transform player;
    private int totalEnemies;

    [SerializeField]
    private Animator fadeAnimator;

    void Awake() {
        player = FindObjectOfType<PlayerController>().transform;
    }

    void Start() {
        StartCoroutine(Wave(1));
    }

    IEnumerator Wave(int number){
        totalEnemies = Random.Range(2,3) + number * 2;
        waveText.text = number.ToString();
        enemiesText.text = totalEnemies.ToString();

        int tE = totalEnemies;

        for (int i = 0; i < tE; ++i) {
            Vector2 spawnPos = (generateSpawnPos() / 1.5f) * Random.Range(1, totalEnemies/3);
            Instantiate(enemies[Random.Range(0, Mathf.Clamp(number, 0, enemies.Length))], spawnPos, Quaternion.identity);
            yield return new WaitForSeconds(Random.Range(1, 3));
        }

        while (totalEnemies != 0) {
            
            if (player != null) {

                Vector2 spawnPos = generateSpawnPos();

                Vector2 dir = new Vector3(spawnPos.x, spawnPos.y, 0) - player.position;
                float angle = Mathf.Atan2(dir.y,dir.x) * Mathf.Rad2Deg;


                Instantiate(obstacles[Random.Range(0, Mathf.Clamp(number, 0, obstacles.Length))], spawnPos, Quaternion.AngleAxis(angle, Vector3.forward));

            }
            yield return new WaitForSeconds(Random.Range(3, 4));
        }

        StartCoroutine(Wave(number + 1));

        yield return null;
    }

    Vector2 generateSpawnPos() {
        float randomVal = Random.Range(-Mathf.PI, Mathf.PI);
        float vertical = Mathf.Sin(randomVal);
        float horizontal = Mathf.Cos(randomVal);
        Vector2 spawnDir = new Vector2 (horizontal, vertical);
        Vector2 spawnPos = Vector2.zero + spawnDir * 50;
        return spawnPos;
    }

    public void EnemyDied(){
        --totalEnemies;
        enemiesText.text = totalEnemies.ToString();
    }
    
    public void PlayerDied() {
        fadeAnimator.SetTrigger("Fade");
        Invoke("Highscore", 2f);
    }

    private void Highscore() {
        SceneManager.LoadScene("HighScorepage");
    }
}