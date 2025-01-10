import yfinance as yf

# 东方甄选的股票代码
stock_symbol = "1797.HK"

# 获取股票数据
stock_data = yf.Ticker(stock_symbol)

# 获取历史数据
hist_data = stock_data.history(period="max")

# 将数据保存到CSV文件
csv_file_path = "eastern_selection_stock_data.csv"
hist_data.to_csv(csv_file_path)

print(f"数据已保存到 {csv_file_path}")
