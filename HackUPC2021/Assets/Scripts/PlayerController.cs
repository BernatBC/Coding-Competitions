using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    public static PlayerController playerController;

    [SerializeField]
    private GameObject explosionSound;
    
    [SerializeField]
    private GameObject explosion;

    [SerializeField]
    private float speed;

    [SerializeField]
    private GameObject bullet;
    
    [SerializeField]
    private Transform cannon;
    
    private Rigidbody2D rb2D;

    private float nextFire = 0;
    [SerializeField]
    private float fireDelay;

    void Awake()
    {
        rb2D = GetComponent<Rigidbody2D>();
        playerController = this;
    }

    void Update()
    {
        rb2D.velocity = new Vector2(Input.GetAxis("Horizontal")*speed, Input.GetAxis("Vertical")*speed);

        Vector3 dir = Camera.main.ScreenToWorldPoint(Input.mousePosition) - transform.position;
        float angle = Mathf.Atan2(dir.y, dir.x) * Mathf.Rad2Deg;
        transform.rotation = Quaternion.AngleAxis(angle, Vector3.forward);

        if (Input.GetMouseButton(0) &&  Time.time > nextFire) {
            Instantiate(bullet, cannon.position, transform.rotation);
            nextFire = Time.time + fireDelay;
        }
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.tag == "Asteroid" || collision.tag == "Enemy Bullet") {
            Destroy(collision.gameObject);
            EndGame();
        }
    }

    public void EndGame() {
        int score = Score_manager.score_manager.Score();
        Highscore_manager.highscore_Manager.Update_highscore(score);
        Cursor.SetCursor(null, Vector2.zero, CursorMode.Auto);
        FindObjectOfType<LevelManager>().PlayerDied();
        
        GameObject g =  Instantiate(explosion, transform.position, Quaternion.identity);
        Destroy(g, 4f);
        GameObject sound = Instantiate(explosionSound);
        Destroy(sound, 2f);
        
        CinemachineShake.Instance.ShakeCamera(6f, 0.75f);

        Destroy(this.gameObject);
    }
}