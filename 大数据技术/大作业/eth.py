from google.cloud import bigquery
import pandas as pd

# 设置BigQuery客户端
client = bigquery.Client()

# 定义SQL查询
query = """
    SELECT *
    FROM `bigquery-public-data.crypto_ethereum.transactions`
    WHERE DATE(block_timestamp) = '2022-09-15'
    LIMIT 200
"""

# 执行查询
query_job = client.query(query)

# 获取查询结果
results = query_job.result()

# 将结果转换为DataFrame
df = pd.DataFrame([dict(row) for row in results])

# 保存到本地CSV文件
df.to_csv("ethereum_transactions_2022_09_15.csv", index=False)

print("数据已保存到 ethereum_transactions_2022_09_15.csv")