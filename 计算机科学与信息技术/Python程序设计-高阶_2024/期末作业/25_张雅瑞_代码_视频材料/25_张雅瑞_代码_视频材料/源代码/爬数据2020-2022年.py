import requests
from bs4 import BeautifulSoup
import pandas as pd


def fetch_top_movies(year):
    url = f'https://www.the-numbers.com/market/{year}/top-grossing-movies'
    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/85.0.4183.121 Safari/537.36'
    }

    try:
        response = requests.get(url, headers=headers)
        response.raise_for_status()  # 确保请求成功
        soup = BeautifulSoup(response.text, 'html.parser')

        movies = []

        # 找到包含电影数据的表格
        table = soup.find('table')
        if table:
            rows = table.find_all('tr')
            for row in rows[1:101]:  # 获取前100行数据
                columns = row.find_all('td')
                if columns:
                    rank = columns[0].get_text(strip=True)
                    movie_title = columns[1].get_text(strip=True)
                    box_office = columns[6].get_text(strip=True)  # 这里的索引可能需要调整
                    release_date = columns[2].get_text(strip=True) if len(columns) > 3 else 'N/A'
                    Genres = columns[4].get_text(strip=True) if len(columns) > 4 else 'N/A'
                    movies.append({
                        'Rank': rank,
                        'Title': movie_title,
                        'Box Office': box_office,
                        'Release Date': release_date,
                        'Genres': Genres,
                        'Year': year
                    })
        return movies

    except requests.exceptions.RequestException as e:
        print(f"Error fetching data for {year}: {e}")
        return []


def fetch_recent_top_movies(years):
    all_movies = []
    for year in years:
        print(f"Fetching top 100 movies for {year}...")
        movies = fetch_top_movies(year)
        all_movies.extend(movies)
    return all_movies


def main():
    recent_years = range(2020, 2023)  # 近3年
    top_movies = fetch_recent_top_movies(recent_years)

    if top_movies:
        # 使用 pandas 将数据写入 Excel
        df = pd.DataFrame(top_movies)
        df.to_excel('top_movies.xlsx', index=False)
        print("数据已成功保存到 top_movies.xlsx 文件中。")
    else:
        print("未能获取电影数据。")


if __name__ == "__main__":
    main()
